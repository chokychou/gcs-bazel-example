#include "absl/strings/string_view.h"
#include "wrapper.h"
#include "absl/strings/str_cat.h"

namespace DbServer
{
    absl::Status CloudStorageOperator::UpdateReader(const std::string &filename)
    {
        auto &client = GetClient();
        auto reader = client.ReadObject(bucket_name_, filename);
        CloudStorageOperator::Closer(reader);
        if (!reader)
        {
            return absl::NotFoundError(absl::StrCat("Error reading object: ", reader.status().message()));
        }

        std::string contents{std::istreambuf_iterator<char>{reader}, {}};
        std::cout << contents << "\n";
        return absl::OkStatus();
    }

    absl::Status CloudStorageOperator::UpdateWriter(const std::string &data, const std::string &filename)
    {
        auto &client = GetClient();
        auto writer = client.WriteObject(bucket_name_, filename);
        writer << data;
        CloudStorageOperator::Closer(writer);
        if (!writer.metadata())
        {
            return absl::InternalError(absl::StrCat("Error writing object: ", writer.metadata().status().message()));
        }
        std::cout << "Successfully created object: " << *writer.metadata() << "\n";
        return absl::OkStatus();
    }

    template <typename T>
    void CloudStorageOperator::Closer(T &agent)
    {
        agent.Close();
        std::cout << typeid(T).name() << " Agent closed." << std::endl;
    }
} // DbServer
