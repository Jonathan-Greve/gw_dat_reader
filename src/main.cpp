#include <iostream>
#include <flatbuffers/flatbuffers.h>
#include <gwdat_filename_generated.h>
#include <gwdat_terrain_generated.h>

int main() {
    // Create a FlatBufferBuilder
    flatbuffers::FlatBufferBuilder builder;

    // Create a GWDatfilename
    auto filename = GWDat::CreateGWDatfilename(builder, 1, 2);

    // Create a GWDatTerrain
    auto terrain = GWDat::CreateGWDatTerrain(builder, 123, filename, 456);

    // Create a TerrainReply
    auto reply = GWDat::CreateTerrainReply(builder, terrain);

    // Finish the buffer
    builder.Finish(reply);

    // Get the buffer pointer and size
    uint8_t* buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    // Parse the buffer
    auto parsed_reply = GWDat::GetTerrainReply(buf);

    // Print the parsed data
    std::cout << "file_id: " << parsed_reply->gw_dat_terrain()->file_id() << std::endl;
    std::cout << "id0: " << parsed_reply->gw_dat_terrain()->gwdat_filename()->id0() << std::endl;
    std::cout << "id1: " << parsed_reply->gw_dat_terrain()->gwdat_filename()->id1() << std::endl;
    std::cout << "file_size: " << parsed_reply->gw_dat_terrain()->file_size() << std::endl;

    return 0;
}