// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_GWDATFILENAME_GWDAT_H_
#define FLATBUFFERS_GENERATED_GWDATFILENAME_GWDAT_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 5 &&
              FLATBUFFERS_VERSION_REVISION == 26,
             "Non-compatible flatbuffers version included");

namespace GWDat {

struct GWDatfilename;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(2) GWDatfilename FLATBUFFERS_FINAL_CLASS {
 private:
  uint16_t id0_;
  uint16_t id1_;

 public:
  GWDatfilename()
      : id0_(0),
        id1_(0) {
  }
  GWDatfilename(uint16_t _id0, uint16_t _id1)
      : id0_(::flatbuffers::EndianScalar(_id0)),
        id1_(::flatbuffers::EndianScalar(_id1)) {
  }
  uint16_t id0() const {
    return ::flatbuffers::EndianScalar(id0_);
  }
  uint16_t id1() const {
    return ::flatbuffers::EndianScalar(id1_);
  }
};
FLATBUFFERS_STRUCT_END(GWDatfilename, 4);

}  // namespace GWDat

#endif  // FLATBUFFERS_GENERATED_GWDATFILENAME_GWDAT_H_
