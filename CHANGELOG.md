# Changelog

## [Unreleased] - Project Modernization

### Build System (CMakeLists.txt)
- Lowered `cmake_minimum_required` from 3.21 to 3.14
- Added `find_package(libzip REQUIRED)` with proper error diagnostics
- Added `target_include_directories(xjava PRIVATE src/)` — all includes now relative to `src/`
- Added compiler warning flags: `-Wall -Wextra -Wpedantic` (GCC/Clang), `/W4` (MSVC)
- Added `CMAKE_CXX_STANDARD_REQUIRED ON` and `CMAKE_CXX_EXTENSIONS OFF`
- Added `install(TARGETS xjava DESTINATION bin)`
- Added `enable_testing()` and `add_subdirectory(tests)` for CTest integration
- Added platform-conditional `Shlwapi` linking on Windows
- Changed `target_link_libraries` from bare `zip` to `libzip::zip` (proper imported target)

### Cross-Platform (std::filesystem)
- **`FilePath.cpp`**: Replaced all POSIX-specific code (`dirent.h`, `sys/stat.h`, `getcwd`, `realpath`, `lstat`, `opendir`/`readdir`) with C++17 `std::filesystem`
  - `absolutePath()` → `std::filesystem::absolute()` + `std::filesystem::weakly_canonical()`
  - `cwd()` → `std::filesystem::current_path()`
  - `exists()` → `std::filesystem::exists()` — **fixed file handle leak** (old code used `fopen` without `fclose`)
  - `isDir()` → `std::filesystem::is_directory()`
  - `list()` → `std::filesystem::directory_iterator()`
  - Removed all `#if defined(__linux__)` / `#ifdef _MSC_VER` guards — now platform-agnostic
- **`ClassPath.cpp`**: Fixed class name separator bug — `'.'` now always converts to `'/'` (was `FilePath::separator[0]`, which would be `'\\'` on Windows)
- **`ClassPath.cpp`**: Simplified `getJrePath()` — removed platform-specific `#if`/`#ifdef` branches
- **`Entry.cpp`**: Fixed `CompositeEntry::separator` — now `":"` on Unix, `";"` on Windows (was `";"` on both)
- **`Entry.cpp`**: All hardcoded `";"` separators now use `CompositeEntry::separator` constant

### ODR Violation Fixes (Static Globals in Headers)
- **`Class.h`**: `static std::map primitiveTypes` → `inline const std::map primitiveTypes` (C++17)
- **`StringPool.h`**: Moved `static std::map internedStrings` from header to `StringPool.cpp`; added `allInternedStrings()` getter for GC root collection
- **`NativeRegistry.h`**: Moved `static std::map registry` from header to `NativeRegistry.cpp`
- **`Exception.h`**: `static` functions → `inline` functions; fixed `exception()` parameter from pass-by-value to `const std::string&`

### Memory Leak Fixes (Smart Pointers)
- **`Instruction` (interpreter loop)**: `instruction::create()` now returns `std::unique_ptr<Instruction>` — **fixed per-instruction memory leak** in the main interpreter loop
- **`BytesReader`**: Replaced raw `u1* buffer` with `std::vector<u1>` — **fixed buffer leak** (old code had no destructor and a double-allocation bug); replaced `fopen`/`fread`/`fclose` with `std::ifstream`
- **`Method::exceptionTable`**: `ExceptionTable*` → `std::unique_ptr<ExceptionTable>` — removed manual `delete` in destructor
- **`Slots::data`**: `Slot* data` with manual new/delete → `std::vector<Slot> data` — eliminated manual copy constructor, assignment operator, and destructor (Rule of Zero)
- **`ClassFile::interfaces`**: `u2* interfaces` (raw array) → `std::vector<u2> interfaces`
- **`GZipPool`**: Now returns `std::optional<std::vector<u1>>` instead of raw `new unsigned char[]` with ambiguous ownership; added `closeAll()` to clean up cached zip handles

### Code Style Modernization
- **`basicType.h`**: Replaced all `typedef` with `using`; replaced `#define` type aliases and constants with `inline constexpr`; added `<cstdint>` for portable integer types (`uint8_t`, `uint16_t`, `uint32_t`, `uint64_t`) — **fixes `unsigned long` being 4 bytes on Win64**
- **Include guards**: Replaced `#ifndef`/`#define`/`#endif` with `#pragma once` in all modified headers
- **Include paths**: Fixed `../../src/basicType.h` → `basicType.h` (leveraging CMake `target_include_directories`); fixed double slashes (`../common//Console.h` → `../common/Console.h`)
- **C-style casts → C++ casts**: Replaced `reinterpret_cast`, `static_cast` in `ClassFile.cpp`, `Method.cpp`, `NativeRegistry.cpp`, `instruction.cpp`
- **`memset`/`memcpy` → `std::fill`/`std::copy`/`std::memcpy`**: Slots.cpp now uses `std::memcpy` for type punning (float↔int, double↔long) instead of C-style casts
- **`typedef` → `using`**: `Frame.h` — `typedef Slots LocalVars` → `using LocalVars = Slots`
- **Const-correctness**: `Class::getMethods()`, `getFields()`, `getConstructors()` now `const`; `Instruction::verbose()` and all overrides now `const`
- **Removed unnecessary `#include <iostream>`** from headers that don't use it

### CI & Tests
- **GitHub Actions** (`.github/workflows/build.yml`): Build matrix across `ubuntu-latest`, `macos-latest`, `windows-latest` with automatic libzip installation; added ASan/UBSan sanitizer job
- **GoogleTest**: Added via CMake `FetchContent` (v1.14.0)
- **CMake**: Extracted `xjava_lib` static library to eliminate duplicate source file lists between `xjava` and `xjava_tests`
- **Test consolidation**: Deleted old `test/` directory (raw `execute()` harnesses with no assertions); cleaned up `main.cpp` `TEST_MODE` block. All tests now live in `tests/` using GoogleTest
- **65 unit tests** across 9 suites:
  - `SlotTest` (1): default values
  - `SlotsTest` (9): int/float/long/double/bool/ref get/set, copy, resize
  - `SlotsStackTest` (7): push/pop all types, clear
  - `BytesReaderTest` (5): buffer read, U1, sourceFile, end, read bytes
  - `FilePathTest` (9): trim, case, start/endsWith, split, join, exists, cwd
  - `InstructionReaderTest` (8): readUint8/16, readInt16/32, PC tracking, reset, skipPadding
  - `MethodDescriptorParserTest` (10): no-args, primitives, objects, arrays, multi-dim, complex
  - `StackTest` (4): empty, push/pop, LIFO ordering, multiple operations
  - `FrameTest` (12): local vars (all types), operand stack (all types), mixed ops, branch
- **Fixed `MethodDescriptorParser`**: Rewrote `parseFieldType()` to peek without consuming — the old code called `readChar()` in the default case without unreading, causing the `)` delimiter to be consumed. The parser now works correctly in both Debug and Release builds. Replaced `assert()` with `exception::panic()` for proper error reporting.

### Bug Fixes
- **`fastore`**: Fixed inverted null check (`if (object)` → `if (!object)`) — would crash on valid refs and silently proceed on null
- **`Attributes.cpp:498`**: Fixed loop condition `i > numAnnotations` → `i < numAnnotations` — type annotations were never parsed
- **`Attributes.cpp:433,458`**: Fixed bitwise `&` → logical `&&` in StackMapFrame type range checks
- **`Attributes.cpp`**: Fixed 8 `reserve()` → `resize()` bugs — `reserve` does not change `size()`, so `[i] =` was undefined behavior
- **`AttributeSourceDebugExtension`**: Fixed uninitialized pointer read — allocated buffer once, read once

### Code Compression (Modern C++ Refactoring)
- **`instruction/`**: Replaced 7 category files (constants, loads, stores, math, conversions, comparisons, control) with C++17 template-based instructions in `instructions.h/.cpp`
  - `IndexedLoad/Store`, `FixedSlotLoad/Store`, `ArrayLoad/Store`, `BinMath`, `UnaryMath`, `Conversion`, `CmpAndPush`, `IfBranch`, `IfCmpBranch`, `TypedReturn`, `ConstPush` templates
  - Opcode dispatch: static table replaces 210-case switch in `create()` and `name()`
  - **3,885 → 2,485 lines** (−1,400 lines, −36%)
- **`native/`**: Data-driven registration table replaces 21 `doRegistration()` functions
  - Single `nativeTable[]` array in `NativeRegistry.cpp` with all 72 entries
  - Removed `doRegistration()` from 22 .cpp files and 22 .h files
  - **2,394 → 2,312 lines** (−82 lines)
- **`classfile/`**: Merged 3 MemberRef classes + map-based attribute factory
  - `ConstantFieldRef`/`ConstantMethodRef`/`ConstantInterfaceMethodRef` → single `ConstantMemberRef` with `MemberRefKind` enum
  - 23-branch if/else in `AttributeInfo::from()` → `std::unordered_map` lookup
  - **2,067 → 2,011 lines** (−56 lines)
- **Total compression**: 12,951 → 11,413 source lines (−1,538 lines, −12%)
