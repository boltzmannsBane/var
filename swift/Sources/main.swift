import Foundation
import NIO
import NIOHTTP1

let server = HTTPServer(group: MultiThreadedEventLoopGroup(numberOfThreads: System.coreCount))

server.listen(on: 8080) { (request, response) in
    switch request.uri {
    case "/":
        response.send("Hello, world!")
    case "/hello":
        response.send("Hello, \(request.queryParameters["name"] ?? "world")!")
    default:
        response.statusCode = .notFound
        response.send("Not found")
    }
}

print("Server started on port 8080")
