/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Microsoft Corporation
 * 
 * -=- Robust Distributed System Nucleus (rDSN) -=- 
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

# include <dsn/internal/utils.h>

# include <gtest/gtest.h>

using namespace ::dsn;
using namespace ::dsn::utils;

TEST(core, binary_io)
{
    int value = 0xdeadbeef;
    binary_writer writer;
    writer.write(value);

    binary_reader reader(writer.get_buffer());
    int value3;
    reader.read(value3);

    EXPECT_TRUE(value3 == value);
}


TEST(core, binary_io_with_pos)
{
    int value = 0xdeadbeef;
    int value2 = 0xdeadbeef + 100;
    binary_writer writer;
    auto pos = writer.write_placeholder();
    
    writer.write(value);
    writer.write(value2, pos);
    
    binary_reader reader(writer.get_buffer());
    int value3, value4;
    reader.read(value3);
    reader.read(value4);

    EXPECT_TRUE(value3 == value2);
    EXPECT_TRUE(value4 == value);
}

