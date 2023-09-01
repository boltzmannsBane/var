// The Swift Programming Language
// https://docs.swift.org/swift-book

func sayHello(name: String) {
    print("Hello, \(name)!")
}

if CommandLine.arguments.count != 2 {
    print("Usage: hello NAME")
} else {
    let name = CommandLine.arguments[1]
    sayHello(name: name)
}
