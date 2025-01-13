// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

// Local Headers
#include "cdfw/core/dir_writer.h"
#include "cdfw/core/dir_layout.h"
#include "cdfw/core/vfs.h"
#include "test/mocks/dir_writer.h"
#include "test/mocks/vfs.h"

// Third Party Headers
#include <gtest/gtest.h>

// C++ Standard Library Headers
#include <filesystem>
#include <vector>

namespace cdfw {
namespace {
namespace stdfs = std::filesystem;

class DirWriterStrategyTests : public ::testing::Test {
protected:
  vfs::MockVolume::Data volume_data;
  vfs::MockVolume volume = vfs::MockVolume(volume_data);
  vfs::Path tmp_dir = volume.TempDir() / "test";
  std::shared_ptr<DirWriterStrategy> strategy = DirWriterStrategy::Create();

  void SetUp() override {
    volume_data.Reset();
    volume.CreateDirs(tmp_dir);
    EXPECT_TRUE(volume.Exists(tmp_dir));
  }

  void TearDown() override {
    // volume.RemoveAll(tmp_dir);
    // EXPECT_FALSE(volume.Exists(tmp_dir));
  }
};

TEST_F(DirWriterStrategyTests, Write_DirDoesNotExist) {
  auto p = tmp_dir / "a";
  EXPECT_FALSE(volume.Exists(p));

  strategy->Write(volume, p);
  EXPECT_TRUE(volume.Exists(p));
}

TEST_F(DirWriterStrategyTests, Write_DirAlreadyExists) {
  auto p = tmp_dir / "a";
  volume.CreateDirs(p);
  EXPECT_TRUE(volume.Exists(p));

  strategy->Write(volume, p);
  EXPECT_TRUE(volume.Exists(p));
}

TEST_F(DirWriterStrategyTests, Write_SubDirDoesNotExist) {
  auto p_a = tmp_dir / "a";
  auto p_b = p_a / "b";
  EXPECT_FALSE(volume.Exists(p_a));
  EXPECT_FALSE(volume.Exists(p_b));

  strategy->Write(volume, p_b);
  EXPECT_TRUE(volume.Exists(p_a));
  EXPECT_TRUE(volume.Exists(p_b));
}

TEST(DirWriterTests, Write) {
  vfs::MockVolume::Data volume_data;
  vfs::MockVolume volume = vfs::MockVolume(volume_data);
  vfs::Path tmp_dir = volume.TempDir() / "test";
  auto strategy = std::make_shared<MockDirWriterStrategy>();
  auto writer = DirWriter::Create(strategy);
  DirLayout dir_layout(tmp_dir);

  writer->Write(volume, dir_layout);
  std::vector<vfs::Path> expected_paths = {
      dir_layout.app_dir, dir_layout.routines_dir, dir_layout.data_dir};
  EXPECT_EQ(expected_paths, strategy->paths);
}
} // namespace
} // namespace cdfw