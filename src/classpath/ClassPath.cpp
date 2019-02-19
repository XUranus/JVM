//
// Created by xuranus on 2/6/19.
//

#include "ClassPath.h"
#include "../util/FilePath.h"
#include "../util/Console.h"
#include <cstdlib>

std::string ClassPath::getJrePath(std::string jreOption) {
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

std::string ClassPath::getUserPath(std::string cpOption)
{
    if(cpOption.empty())
        cpOption = FilePath::absolutePath(".");
    return cpOption;
}

ClassPath::ClassPath(std::string jreOption, std::string cpOption)
{
    bootstrapClassPath = Entry::createEntry(FilePath::join(getJrePath(jreOption),"lib/*"));
    extendClassPath = Entry::createEntry(FilePath::join(getJrePath(jreOption),"lib/ext/*"));
    userClassPath = Entry::createEntry(getUserPath(cpOption));
}

void ClassPath::debug()
{
    printf("[classpath info]\n");
    printf("bootstrapPath: %s\n",bootstrapClassPath->toString().c_str());
    printf("extendPath: %s\n",extendClassPath->toString().c_str());
    printf("userPath: %s\n",userClassPath->toString().c_str());
}


std::pair<byte*,int> ClassPath::readClass(std::string classname)
{
    //replace . with /  -> ex:java/lang/Exception
    for(auto &s:classname)
        if(s=='.')
            s = '/';
    // classname won't take ".class" suffix! ->java/lang/Exception.class
    if(!FilePath::hasSuffix(classname,".class"))
        classname = classname + ".class";

    auto ret = bootstrapClassPath->readClass(classname);
    if(ret.first!= nullptr)
        return ret;

    ret = extendClassPath->readClass(classname);
    if(ret.first!= nullptr)
        return ret;

    ret = userClassPath->readClass(classname);
    if(ret.first!= nullptr)
        return ret;

    return std::make_pair(nullptr,0);
}