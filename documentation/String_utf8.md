# String_utf8

This data structure is a UTF8 Unicode character string with lots of utility API functions for finding. modifying, and replacing substrings. This class uses the open source library utf8rewind, which a the time of this writing is available at Github at https://github.com/ZHaskell/utf8rewind under the MIT open source license.

Note: On Linux, building the utf8rewind libray from source produces a so-called "thin" archive, where the libutf8rewind.a file only contains references to the object files produced in the compilation. To produce a fully populated single stand-along archive library file, run the following shell script in the utf8rewind-master/output/linux/x86/Release directory:

```
for lib in `find -name '*.a'`;
    do ar -t $lib | xargs ar rvs $lib.new && mv -v $lib.new $lib;
done
```

### Protocols Supported

none
