// TODO make test

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "wrapper.h"

TEST(StorageMockingSamples, MockReadObject) {
  namespace gcs = ::google::cloud::storage;

  std::shared_ptr<gcs::testing::MockClient> mock =
      std::make_shared<gcs::testing::MockClient>();
  auto client = gcs::testing::UndecoratedClientFromMock(mock);

  std::string const text = "this is a mock http response";
  std::size_t offset = 0;
  // Simulate a Read() call in the MockObjectReadSource object created below
  auto simulate_read = [&text, &offset](void* buf, std::size_t n) {
    auto const l = (std::min)(n, text.size() - offset);
    std::memcpy(buf, text.data() + offset, l);
    offset += l;
    return gcs::internal::ReadSourceResult{
        l, gcs::internal::HttpResponse{200, {}, {}}};
  };
  EXPECT_CALL(*mock, ReadObject)
      .WillOnce([&](gcs::internal::ReadObjectRangeRequest const& request) {
        EXPECT_EQ(request.bucket_name(), "mock-bucket-name") << request;
        std::unique_ptr<gcs::testing::MockObjectReadSource> mock_source(
            new gcs::testing::MockObjectReadSource);
        ::testing::InSequence seq;
        EXPECT_CALL(*mock_source, IsOpen()).WillRepeatedly(Return(true));
        EXPECT_CALL(*mock_source, Read).WillOnce(simulate_read);
        EXPECT_CALL(*mock_source, IsOpen()).WillRepeatedly(Return(false));

        return google::cloud::make_status_or(
            std::unique_ptr<gcs::internal::ObjectReadSource>(
                std::move(mock_source)));
      });

  gcs::ObjectReadStream stream =
      client.ReadObject("mock-bucket-name", "mock-object-name");

  // Reading the payload of http response stored in stream
  std::string actual{std::istreambuf_iterator<char>(stream), {}};
  EXPECT_EQ(actual, text);
  stream.Close();
}


TEST(StorageMockingSamples, MockReadObjectFailure) {
  namespace gcs = ::google::cloud::storage;

  std::shared_ptr<gcs::testing::MockClient> mock =
      std::make_shared<gcs::testing::MockClient>();
  auto client = gcs::testing::UndecoratedClientFromMock(mock);

  std::string text = "this is a mock http response";
  EXPECT_CALL(*mock, ReadObject)
      .WillOnce([](gcs::internal::ReadObjectRangeRequest const& request) {
        EXPECT_EQ(request.bucket_name(), "mock-bucket-name") << request;
        auto* mock_source = new gcs::testing::MockObjectReadSource;
        ::testing::InSequence seq;
        EXPECT_CALL(*mock_source, IsOpen).WillRepeatedly(Return(true));
        EXPECT_CALL(*mock_source, Read)
            .WillOnce(Return(google::cloud::Status(
                google::cloud::StatusCode::kInvalidArgument,
                "Invalid Argument")));
        EXPECT_CALL(*mock_source, IsOpen).WillRepeatedly(Return(false));

        std::unique_ptr<gcs::internal::ObjectReadSource> result(mock_source);

        return google::cloud::make_status_or(std::move(result));
      });

  gcs::ObjectReadStream stream =
      client.ReadObject("mock-bucket-name", "mock-object-name");
  EXPECT_TRUE(stream.bad());
  stream.Close();
}

TEST(StorageMockingSamples, MockWriteObject) {
  namespace gcs = ::google::cloud::storage;

  std::shared_ptr<gcs::testing::MockClient> mock =
      std::make_shared<gcs::testing::MockClient>();
  auto client = gcs::testing::UndecoratedClientFromMock(mock);

  gcs::ObjectMetadata expected_metadata;

  using gcs::internal::CreateResumableUploadResponse;
  using gcs::internal::QueryResumableUploadResponse;
  EXPECT_CALL(*mock, CreateResumableUpload)
      .WillOnce(Return(CreateResumableUploadResponse{"test-only-upload-id"}));
  EXPECT_CALL(*mock, UploadChunk)
      .WillOnce(Return(QueryResumableUploadResponse{
          /*.committed_size=*/absl::nullopt,
          /*.object_metadata=*/expected_metadata}));

  auto stream = client.WriteObject("mock-bucket-name", "mock-object-name");
  stream << "Hello World!";
  stream.Close();

}

TEST(StorageMockingSamples, MockWriteObjectFailure) {
  namespace gcs = ::google::cloud::storage;

  std::shared_ptr<gcs::testing::MockClient> mock =
      std::make_shared<gcs::testing::MockClient>();
  auto client = gcs::testing::UndecoratedClientFromMock(mock);

  using gcs::internal::CreateResumableUploadResponse;
  using gcs::internal::QueryResumableUploadResponse;
  EXPECT_CALL(*mock, CreateResumableUpload)
      .WillOnce(Return(CreateResumableUploadResponse{"test-only-upload-id"}));
  EXPECT_CALL(*mock, UploadChunk)
      .WillOnce(Return(google::cloud::Status{
          google::cloud::StatusCode::kInvalidArgument, "Invalid Argument"}));

  auto stream = client.WriteObject("mock-bucket-name", "mock-object-name");
  stream << "Hello World!";
  stream.Close();

  EXPECT_TRUE(stream.bad());
}