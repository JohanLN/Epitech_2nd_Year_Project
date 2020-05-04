/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Core header
*/

#include <string>
#include <memory>
#include <dlfcn.h>
#include <iostream>

template <class T>
class DLLoader {
public:
    DLLoader(std::string const& libName) :  _handle(nullptr), _libName(libName)
    {
    }

    ~DLLoader() = default;

    void DLOpenLib()
    {
        if (!(_handle = dlopen(_libName.c_str(), RTLD_LAZY))) {
            std::cerr << dlerror() << std::endl;
            exit(84);
        }
    }

    void DLCloseLib() {
        if (dlclose(_handle) != 0) {
            std::cerr << dlerror() << std::endl;
            exit(84);
        }
    }

    T* getInstance()
    {
        T * (*load) ();
        load = (T*(*)())dlsym(_handle, "entryPoint");
        return load();
    }

    DLLoader& operator=(const DLLoader& oldLoader)
    {
        _libName = oldLoader._libName;
        _handle = oldLoader._handle;
    }
    void *_handle;
private:
    std::string _libName;
};