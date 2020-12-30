//
// Created by xuranus on 2/6/19.
//

#include "ClassPath.h"
#include "../util/FilePath.h"
#include "../util/Console.h"
#include <cstdlib>

std::string ClassPath::getJrePath(const std::string& jreOption) {
    //priority Xbootpath -> ./jre -> $JAVA_HOME/jre
    auto env = getenv("JAVA_HOME");
    if(!jreOption.empty() && FilePath::pathExists(jreOption))
        return jreOption;
    else if(FilePath::pathExists("./jre"))
        return "./jre";
    else if(env!= nullptr)
        return FilePath::join(std::string(env),"jre");
    else {
        Console::printlnError("Can not find jre path.\n");
        exit(1);
    }
}

std::string ClassPath::getUserPath(const std::string& _cpOption)
{
    std::string cpOption = _cpOption;
    if(cpOption.empty())
        cpOption = FilePath::absolutePath(".");
    return cpOption;
}

ClassPath::ClassPath(const std::string& jreOption, const std::string& cpOption)
{
    bootstrapClassPath = Entry::createEntry(FilePath::join(getJrePath(jreOption),"lib/*"));
    extendClassPath = Entry::createEntry(FilePath::join(getJrePath(jreOption),"lib/ext/*"));
    userClassPath = Entry::createEntry(getUserPath(cpOption));
}

ClassPath::~ClassPath() {
    delete bootstrapClassPath;
    delete extendClassPath;
    delete userClassPath;
}

void ClassPath::debug()
{
    printf("[classpath info]\n");
    printf("bootstrapPath: %s\n",bootstrapClassPath->toString().c_str());
    printf("extendPath: %s\n",extendClassPath->toString().c_str());
    printf("userPath: %s\n",userClassPath->toString().c_str());
}


int ClassPath::readClass(const std::string& _classname,byte*& data)
{
    //replace . with /  -> ex:java/lang/Exception
    std::string classname = _classname;
    for(auto &s:classname)
        if(s=='.')
            s = '/';
    // classname won't take ".class" suffix! ->java/lang/Exception.class
    if(!FilePath::hasSuffix(classname,".class"))
        classname = classname + ".class";

    int n_bytes = 0;

    n_bytes = bootstrapClassPath->readClass(classname, data);
    if(n_bytes >= 0) return n_bytes;

    n_bytes = extendClassPath->readClass(classname, data);
    if(n_bytes >= 0) return n_bytes;

    n_bytes = userClassPath->readClass(classname, data);
    if(n_bytes >= 0) return n_bytes;

    //fail
    return -1;
}