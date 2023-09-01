// swift-tools-version: 5.8

import PackageDescription

let package = Package(
    name: "swift",
    targets: [
        // Targets are the basic building blocks of a package, defining a module or a test suite.
        // Targets can depend on other targets in this package and products from dependencies.
        .executableTarget(
            name: "swift",
            path: "Sources"),
    ],
    dependencies: [
        .product(name: "NIOCore", package: "NIO"),
        .product(name: "NIOPosix", package: "NIO"),
        .product(name: "NIOHTTP1", package: "NIO")
    ]
)
