#include <iostream>

#include <memory>

#include "constants.h"
#include "wrapper.h"

// Create aliases to make the code easier to read.
int main(int argc, char *argv[])
{
    const std::string bucket_name = DbServer::kBucketName;

    auto agent = std::make_unique<DbServer::CloudStorageOperator>(DbServer::CloudStorageOperator(bucket_name));

    const std::string filename = "quickstart-grpc.txt";

    // Create proto here
    
    auto write_status = agent->UpdateWriter("hello world", filename);
    if (!write_status.ok()) {
        std::cerr << "Error writing to file: " << filename << "\n";
        return 0;
    }

    auto read_status = agent->UpdateReader(filename);
    if (!read_status.ok()) {
        std::cerr << "Error reading from file: " << filename << "\n";
        return 0;
    }

    return 0;
}
