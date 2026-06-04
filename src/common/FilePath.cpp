#include "FilePath.h"
#include "Exception.h"

#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

#ifdef _WIN32
std::string FilePath::separator = "\\";
#else
std::string FilePath::separator = "/";
#endif

std::string FilePath::absolutePath(const std::string& path) {
    std::error_code ec;
    auto abs = fs::absolute(path, ec);
    if (ec) {
        // fallback: if path doesn't exist, try resolving relative to cwd
        if (path.empty()) {
            return absolutePath(".");
        }
        if (startsWith(path, separator)) {
            return path;
        }
        if (startsWith(path, ".")) {
            return join(absolutePath("."), path.substr(1));
        }
        return join(absolutePath("."), path);
    }
    // normalize the path (resolve .., ., etc.)
    auto canonical = fs::weakly_canonical(abs, ec);
    if (ec) {
        return abs.string();
    }
    return canonical.string();
}

std::string FilePath::join(const std::string& _path, const std::string& _filename) {
    std::string path = trim(_path);
    std::string filename = trim(_filename);
    if (endsWith(path, separator)) {
        path = path.substr(0, path.length() - 1);
    }
    if (startsWith(filename, separator)) {
        filename = filename.substr(1);
    }
    return path + separator + filename;
}

bool FilePath::endsWith(const std::string& str, const std::string& suffix) {
    if (suffix.length() > str.length()) return false;
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

bool FilePath::startsWith(const std::string& str, const std::string& prefix) {
    return str.compare(0, prefix.length(), prefix) == 0;
}

std::string FilePath::cwd() {
    std::error_code ec;
    auto p = fs::current_path(ec);
    if (ec) {
        exception::panic("failed to get current working directory");
    }
    return p.string();
}

std::string FilePath::trim(const std::string& str) {
    auto start = str.find_first_not_of(' ');
    if (start == std::string::npos) return "";
    auto end = str.find_last_not_of(' ');
    return str.substr(start, end - start + 1);
}

std::string FilePath::lowerCase(const std::string& str) {
    std::string res = str;
    for (char& ch : res) {
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }
    }
    return res;
}

std::string FilePath::upperCase(const std::string& str) {
    std::string res = str;
    for (char& ch : res) {
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - 'a' + 'A';
        }
    }
    return res;
}

std::vector<std::string> FilePath::split(const std::string& s, const std::string& c) {
    std::vector<std::string> v;
    std::string::size_type pos1 = 0;
    auto pos2 = s.find(c);
    while (std::string::npos != pos2) {
        v.push_back(s.substr(pos1, pos2 - pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length()) {
        v.push_back(s.substr(pos1));
    }
    return v;
}

bool FilePath::isDir(const std::string& path) {
    std::error_code ec;
    return fs::is_directory(path, ec);
}

std::vector<std::string> FilePath::list(const std::string& path) {
    std::vector<std::string> ret;
    std::error_code ec;
    auto absDir = absolutePath(path);
    if (!fs::is_directory(absDir, ec)) {
        return ret;
    }
    for (const auto& entry : fs::directory_iterator(absDir, ec)) {
        auto name = entry.path().filename().string();
        if (name != "." && name != "..") {
            ret.push_back(name);
        }
    }
    return ret;
}

std::vector<std::string> FilePath::listDir(const std::string& path) {
    std::vector<std::string> res;
    auto absDir = absolutePath(path);
    std::error_code ec;
    for (const auto& entry : fs::directory_iterator(absDir, ec)) {
        if (entry.is_directory()) {
            res.push_back(entry.path().filename().string());
        }
    }
    return res;
}

std::vector<std::string> FilePath::listZip(const std::string& path) {
    auto files = list(absolutePath(path));
    std::vector<std::string> res;
    for (const auto& file : files) {
        auto lc = lowerCase(file);
        if (endsWith(lc, ".jar") || endsWith(lc, ".zip")) {
            res.push_back(file);
        }
    }
    return res;
}

bool FilePath::exists(const std::string& path) {
    std::error_code ec;
    return fs::exists(path, ec);
}
