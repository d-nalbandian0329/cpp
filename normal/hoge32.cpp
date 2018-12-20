// Allocator : Encapsulates a memory allocation and deallocation strategy.
// ex.)
// template <class T, class Allocator = std::allocator>
// class vector;

// 独自のallocatorを使う理由
// デフォルトのnew/deleteが遅いためより高速になるように最適化した
// メモリ割り当て機構を作るなど
// ex.) 巨大なメモリプールを確保しておいてそこから切り出していく

// since C++11
// destructorを除くallocatorクラスのメンバ関数はデータ競合を引き起こさない
// そのため複数スレッドから同時にallocaorクラスのメンバ関数が呼ばれた
// としても正しくメモリ確保・解放される



