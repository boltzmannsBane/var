#!/bin/bash

# Remove previous image if it exists
docker rmi -f flask_app

# Build the Docker image
docker build -t flask_app . && docker run -p 5000:5000 -v $(pwd):/app flask_app



