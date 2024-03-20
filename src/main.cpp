#include <iostream>
#include <format>
#include <flatbuffers/flatbuffers.h>
#include "gwdat_filename_generated.h"
#include "gwdat_terrain_generated.h"

int main() {
    // Create a FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder;

    // Create a GWDatfilename
    auto filename = GWDat::GWDatfilename(1, 2);

    // Create a GWDatTerrain
    uint32_t file_id = 123;
    uint32_t file_size = 1024;
    auto terrain = GWDat::CreateGWDatTerrain(builder, file_id, &filename, file_size);

    // Finish the buffer
    builder.Finish(terrain);

    // Get the buffer pointer and size
    const uint8_t* buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    // Print the fields using std::format
    std::cout << std::format("GWDatTerrain fields:\n");
    std::cout << std::format("  file_id: {}\n", file_id);
    std::cout << std::format("  gwdat_filename: {{\n");
    std::cout << std::format("    id0: {}\n", flatbuffers::GetRoot<GWDat::GWDatTerrain>(buf)->gwdat_filename()->id0());
    std::cout << std::format("    id1: {}\n", flatbuffers::GetRoot<GWDat::GWDatTerrain>(buf)->gwdat_filename()->id1());
    std::cout << std::format("  }}\n");
    std::cout << std::format("  file_size: {}\n", file_size);
    std::cout << std::format("Buffer size: {} bytes\n", size);

    return 0;
}