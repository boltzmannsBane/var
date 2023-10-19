from python import Python

var np: PythonObject = None


fn load():
    try:
        # this doesn't compile outside of a try block.
        # usage of try-except blocks should be documented in the Mojo doc
        # as their usage is enforced by the compiler
        np = Python.import_module("numpy")
    except:
        pass


fn main():
    load()
    np_test()


fn np_test():
    var ar: PythonObject = None
    try:
        ar = np.arange(15).reshape(3, 5)
        print(ar)
        print(ar.shape)
    except:
        pass
