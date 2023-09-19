to run the project:

docker build -t <image_name> .
docker run --rm -it -v $(pwd):/app <image_name> /bin/bash
