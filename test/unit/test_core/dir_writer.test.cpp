// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_writer.h"
#include "cdfw/core/dir_layout.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <filesystem>
#include <vector>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

class MockDirWriterStrategy : public DirWriterStrategy {
public:
  std::vector<stdfs::path> paths;

  MockDirWriterStrategy() = default;
  ~MockDirWriterStrategy() = default;

  virtual void Write(const stdfs::path &path) override final {
    paths.push_back(path);
  }
};

class DirWriterStrategyTests : public ::testing::Test {
public:
  stdfs::path tmp_dir = stdfs::temp_directory_path() / "test";
  std::shared_ptr<DirWriterStrategy> strategy = DirWriterStrategy::Create();

  void SetUp() override {
    stdfs::create_directories(tmp_dir);
    EXPECT_TRUE(stdfs::exists(tmp_dir));
  }

  void TearDown() override { stdfs::remove_all(tmp_dir); }
};

TEST_F(DirWriterStrategyTests, Write_DirDoesNotExist) {
  auto p = tmp_dir / "a";
  EXPECT_FALSE(stdfs::exists(p));

  strategy->Write(p);
  EXPECT_TRUE(stdfs::exists(p));
}

TEST_F(DirWriterStrategyTests, Write_DirAlreadyExists) {
  auto p = tmp_dir / "a";
  stdfs::create_directories(p);
  EXPECT_TRUE(stdfs::exists(p));

  strategy->Write(p);
  EXPECT_TRUE(stdfs::exists(p));
}

TEST_F(DirWriterStrategyTests, Write_SubDirDoesNotExist) {
  auto p_a = tmp_dir / "a";
  auto p_b = p_a / "b";
  EXPECT_FALSE(stdfs::exists(p_a));
  EXPECT_FALSE(stdfs::exists(p_b));

  strategy->Write(p_b);
  EXPECT_TRUE(stdfs::exists(p_a));
  EXPECT_TRUE(stdfs::exists(p_b));
}

TEST(DirWriterTests, Write) {
  stdfs::path tmp_dir = stdfs::temp_directory_path() / "test";
  auto strategy = std::make_shared<MockDirWriterStrategy>();
  auto writer = DirWriter::Create(strategy);
  DirLayout dir_layout(tmp_dir);

  writer->Write(dir_layout);
  std::vector<stdfs::path> expected_paths = {
      dir_layout.app_dir, dir_layout.routines_dir, dir_layout.data_dir};
  EXPECT_EQ(expected_paths, strategy->paths);
}
} // namespace
} // namespace cdfw