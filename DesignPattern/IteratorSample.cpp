


/**
 * @file: IteratorSample.cpp
 *
 * @brief: Iterator model of the Design pattern.
 *
 * @author: Atsushi Sakai 
 *
 * @copyright (c): 2014 Atsushi Sakai
 *
 * @license : GPL Software License Agreement
 **/

#include <iostream>
#include <vector>

using namespace std;

//クラスのプロトタイプ宣言
class IteratorInterface;
class AggregateInterface;

/**
 * @brief 本のクラス
 */
class Book{
  public:
    /**
     *　本の名前を設定する関数
     */
    void SetName(string name){
      name_=name;
    }

    /**
     * @brief 本の名前を返す関数
     */
    string GetName(void){
      return name_;
    }

  private:
    string name_;//本の名前
};

/**
 *  @brief イテレータ用インターフェースクラス
 */
class IteratorInterface{
  public:
    virtual bool IsLast(void)=0;//最後の要素かどうか
    virtual Book Next(void)=0;//イテレータが指し示すオブジェクトを返して、次のオブジェクトを指す
};

/**
 *  @brief イテレータを使用するデータベースのインターフェースクラス
 */
class AggregateInterface{
  public:
    //イテレータを返す純粋仮想関数
    virtual IteratorInterface* Iterator(void)=0;
};


/**
 *  @brief 本棚を表すクラス
 *         インターフェースクラスであるAggregateを継承している
 **/
class BookShelf : public AggregateInterface{
  public:
    /**
     *  @brief コンストラクタ
     *         引数に本棚の最大サイズを与えること
     *  @param maxsize 本棚の最大サイズ
     **/
    BookShelf(int maxsize){
      books_.resize(maxsize);
      nBooks=0;//本の数の初期化
    }

    /**
     * @brief 指定した本棚のデータを取得する関数
     * @param index 情報を取得したい本のインデックス
     */
    Book GetBookAt(int index){
      return books_[index];
    }

    /**
     * @brief 本をDBに追加する関数
     * @param book 追加する本のデータ
     */
    void AppendBook(Book book){
      books_[nBooks]=book;//DBに追加
      nBooks++;//本の数を一つ増やす
    }

    /**
     * @brief DBに格納された本の数を取得する関数
     */
    int GetNBooks(void){return nBooks;}

    /**
     * @brief BookShelfのイテレータを返す関数
     */
    IteratorInterface* Iterator(void);

  private:
    vector<Book> books_;//本のデータを格納するDB
    int nBooks;//本の数
};

/**
 * @brief BookShelfクラス用イテレータクラス
 */
class BookShelfIterator:public IteratorInterface{
  public:
    BookShelfIterator(BookShelf bookShelf)
    :index_(0),bookShelf_(bookShelf)
    {}

    bool IsLast(void);
    Book Next(void);

  private:
    BookShelf bookShelf_;
    int index_;//イテレータのインデックス
};

/**
 * @brief BookShelfのイテレータを返す関数
 */
IteratorInterface* BookShelf::Iterator(void){
  return new BookShelfIterator(*this);
}



/**
 * @brief イテレータの指し示す要素が最後かどうかを確認する関数
 */
bool BookShelfIterator::IsLast(void){
  if(index_<(bookShelf_.GetNBooks())){
      return true;
  }
  else{
      return false;
  }
}

/**
 * @brief イテレータが指し示す本のデータを返し、
 *        イテレータのインデックスを一つ進める関数
 */
Book BookShelfIterator::Next(void){
  Book book=bookShelf_.GetBookAt(index_);
  index_++;
  return book;
}

int main(void){
  
  //本棚の作成
  BookShelf bookShelf(5);

  //本の登録
  Book book1;
  book1.SetName("Code Complete");
  bookShelf.AppendBook(book1);

  Book book2;
  book2.SetName("Agile Samurai");
  bookShelf.AppendBook(book2);

  Book book3;
  book3.SetName("Effective C++");
  bookShelf.AppendBook(book3);

  //イテレータ作成
  IteratorInterface *it=bookShelf.Iterator();

  while(it->IsLast()){
    Book book=it->Next();

	std::cout << book.GetName() << std::endl;
  }

  return 0;
}

