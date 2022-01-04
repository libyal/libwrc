#!/usr/bin/env python
#
# Python-bindings manifest_resource type test script
#
# Copyright (C) 2011-2021, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import unittest

import pywrc


class ManifestResourceTypeTests(unittest.TestCase):
  """Tests the manifest_resource type."""

  _TEST_DATA = bytes(bytearray([
      0x3c, 0x3f, 0x78, 0x6d, 0x6c, 0x20, 0x76, 0x65, 0x72, 0x73, 0x69, 0x6f,
      0x6e, 0x3d, 0x27, 0x31, 0x2e, 0x30, 0x27, 0x20, 0x65, 0x6e, 0x63, 0x6f,
      0x64, 0x69, 0x6e, 0x67, 0x3d, 0x27, 0x55, 0x54, 0x46, 0x2d, 0x38, 0x27,
      0x20, 0x73, 0x74, 0x61, 0x6e, 0x64, 0x61, 0x6c, 0x6f, 0x6e, 0x65, 0x3d,
      0x27, 0x79, 0x65, 0x73, 0x27, 0x3f, 0x3e, 0x0d, 0x0a, 0x3c, 0x61, 0x73,
      0x73, 0x65, 0x6d, 0x62, 0x6c, 0x79, 0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73,
      0x3d, 0x27, 0x75, 0x72, 0x6e, 0x3a, 0x73, 0x63, 0x68, 0x65, 0x6d, 0x61,
      0x73, 0x2d, 0x6d, 0x69, 0x63, 0x72, 0x6f, 0x73, 0x6f, 0x66, 0x74, 0x2d,
      0x63, 0x6f, 0x6d, 0x3a, 0x61, 0x73, 0x6d, 0x2e, 0x76, 0x31, 0x27, 0x20,
      0x6d, 0x61, 0x6e, 0x69, 0x66, 0x65, 0x73, 0x74, 0x56, 0x65, 0x72, 0x73,
      0x69, 0x6f, 0x6e, 0x3d, 0x27, 0x31, 0x2e, 0x30, 0x27, 0x3e, 0x0d, 0x0a,
      0x20, 0x20, 0x3c, 0x74, 0x72, 0x75, 0x73, 0x74, 0x49, 0x6e, 0x66, 0x6f,
      0x20, 0x78, 0x6d, 0x6c, 0x6e, 0x73, 0x3d, 0x22, 0x75, 0x72, 0x6e, 0x3a,
      0x73, 0x63, 0x68, 0x65, 0x6d, 0x61, 0x73, 0x2d, 0x6d, 0x69, 0x63, 0x72,
      0x6f, 0x73, 0x6f, 0x66, 0x74, 0x2d, 0x63, 0x6f, 0x6d, 0x3a, 0x61, 0x73,
      0x6d, 0x2e, 0x76, 0x33, 0x22, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20,
      0x3c, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74, 0x79, 0x3e, 0x0d, 0x0a,
      0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c, 0x72, 0x65, 0x71, 0x75, 0x65,
      0x73, 0x74, 0x65, 0x64, 0x50, 0x72, 0x69, 0x76, 0x69, 0x6c, 0x65, 0x67,
      0x65, 0x73, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
      0x20, 0x3c, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64, 0x45,
      0x78, 0x65, 0x63, 0x75, 0x74, 0x69, 0x6f, 0x6e, 0x4c, 0x65, 0x76, 0x65,
      0x6c, 0x20, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x3d, 0x27, 0x61, 0x73, 0x49,
      0x6e, 0x76, 0x6f, 0x6b, 0x65, 0x72, 0x27, 0x20, 0x75, 0x69, 0x41, 0x63,
      0x63, 0x65, 0x73, 0x73, 0x3d, 0x27, 0x66, 0x61, 0x6c, 0x73, 0x65, 0x27,
      0x20, 0x2f, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3c,
      0x2f, 0x72, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x65, 0x64, 0x50, 0x72,
      0x69, 0x76, 0x69, 0x6c, 0x65, 0x67, 0x65, 0x73, 0x3e, 0x0d, 0x0a, 0x20,
      0x20, 0x20, 0x20, 0x3c, 0x2f, 0x73, 0x65, 0x63, 0x75, 0x72, 0x69, 0x74,
      0x79, 0x3e, 0x0d, 0x0a, 0x20, 0x20, 0x3c, 0x2f, 0x74, 0x72, 0x75, 0x73,
      0x74, 0x49, 0x6e, 0x66, 0x6f, 0x3e, 0x0d, 0x0a, 0x3c, 0x2f, 0x61, 0x73,
      0x73, 0x65, 0x6d, 0x62, 0x6c, 0x79, 0x3e, 0x0d, 0x0a]))

  def test_copy_from_byte_stream(self):
    """Tests the copy_from_byte_stream function."""
    manifest_resource = pywrc.manifest_resource()
    manifest_resource.copy_from_byte_stream(self._TEST_DATA)

    with self.assertRaises(TypeError):
      manifest_resource.copy_from_byte_stream(None)

    with self.assertRaises(IOError):
      manifest_resource.copy_from_byte_stream(b'')

  def test_get_string(self):
    """Tests the get_string function."""
    manifest_resource = pywrc.manifest_resource()
    manifest_resource.copy_from_byte_stream(self._TEST_DATA)

    manifest_string = manifest_resource.get_string()
    self.assertEqual(manifest_string, self._TEST_DATA.decode('utf-8'))


if __name__ == "__main__":
  unittest.main(verbosity=2)