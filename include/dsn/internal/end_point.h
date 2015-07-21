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
# pragma once

# include <dsn/internal/dsn_types.h>
# include <dsn/internal/utils.h>
# include <dsn/service_api_c.h>

namespace dsn {

#ifndef ZION_NOT_USE_DEFAULT_SERIALIZATION

inline void unmarshall(::dsn::binary_reader& reader, __out_param dsn_address_t& val) 
{
    reader.read_pod(val.ip);
    reader.read_pod(val.port);
    reader.read((char*)val.name, (int)sizeof(val.name));
}

inline void marshall(::dsn::binary_writer& writer, const dsn_address_t& val, uint16_t pos = 0xffff) 
{
    writer.write_pod(val.ip, pos);
    writer.write_pod(val.port, pos);
    writer.write((const char*)val.name, (int)sizeof(val.name), pos);
}

#endif

} // end namespace

namespace std
{
    template<>
    struct hash<dsn_address_t> {
        size_t operator()(const dsn_address_t &ep) const {
            return std::hash<uint32_t>()(ep.ip) ^ std::hash<uint16_t>()(ep.port);
        }
    };
}

inline bool operator == (const dsn_address_t& l, const dsn_address_t& r)
{
    return l.ip == r.ip && l.port == r.port;
}

inline bool operator != (const dsn_address_t& l, const dsn_address_t& r)
{
    return !(l == r);
}

inline bool operator < (const dsn_address_t& l, const dsn_address_t& r)
{
    return l.ip < r.ip || (l.ip == r.ip && l.port < r.port);
}

