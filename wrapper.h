/*
Serialized data are stored in cloud.

Current supported clouds:
  Google Cloud Storage
*/

#ifndef Wrapper_H_
#define Wrapper_H_

#include "google/cloud/storage/client.h"
#include "google/cloud/storage/grpc_plugin.h"
#include "gcs.pb.h"
#include "absl/strings/string_view.h"
#include "absl/status/status.h"

namespace DbServer
{
  // Definition of bucket, directory things like that
  class CloudStorageBase
  {
  public:
    CloudStorageBase() : client_(google::cloud::storage_experimental::DefaultGrpcClient()){};

    ~CloudStorageBase() = default;

    // Returns a reference to the client.
    google::cloud::storage::Client &GetClient() { return client_; }

  private:
    google::cloud::storage::Client client_;
  };

  // Defines methods that operate on Cloud Storage.
  class CloudStorageOperator : public CloudStorageBase
  {
  public:
    CloudStorageOperator(std::string const &bucket_name) : bucket_name_(bucket_name){};

    ~CloudStorageOperator() = default;

    // Reads serialized data from the Cloud Storage.
    absl::Status UpdateReader(const std::string &filename);

    // Writes serialized data to the Cloud Storage.
    absl::Status UpdateWriter(const std::string &data, const std::string &filename);

    template <typename T>
    void Closer(T &agent);

  private:
    std::string bucket_name_;
    DbServer::FcmTokens fcm_tokens_;
  };

} // DbServer

#endif // Wrapper_H_
