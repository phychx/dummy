#pragma once

#include <stdint.h>
#include <float.h>

#define dummy_internal static
#define dummy_global static
#define dummy_persist static

#define DLLExport extern "C" __declspec(dllexport)

#define ArrayCount(Array) (sizeof(Array) / sizeof(Array[0]))
#define First(Array) Array + 0
#define Last(Array, Count) Array + (Count - 1)
#define StructOffset(StructType, StructMember) ((u64)(&(((StructType *)0)->StructMember)))
#define Stringify(Arg) #Arg

#if ASSERT
#define Assert(Expression) if (!(Expression)) { *(volatile int *)0 = 0; }
#else
#define Assert(...)
#endif

#define NotImplemented Assert(!"Not implemented")
#define CTAssert(Expression) static_assert(Expression)

#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t

#define f32 float
#define f64 double

#define bool8 u8
#define bool16 u16
#define bool32 u32

#define umm uintptr_t

#define wchar wchar_t

#define U8_MAX UINT8_MAX
#define U32_MAX UINT32_MAX
#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX