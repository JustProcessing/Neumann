#ifndef PACKETS_H
#define PACKETS_H

// For now naively assume no vectorization

namespace internal {

template <typename T>
struct packet_traits {
  enum {
    Vectorizable = 0
  };
};

}

#endif
