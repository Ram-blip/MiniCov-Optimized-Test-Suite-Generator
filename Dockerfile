FROM ubuntu:22.04

# Set the working directory
# Took help from Copilot to understand the working of the Dockerfile
WORKDIR /app

COPY . .

# Install any needed packages specified in requirements.txt

RUN apt-get update -y && \
    apt-get install -y python3-pip python3-dev


# Install gcc 

RUN apt-get install -y gcc

# Run the runTestScript.c file

RUN gcc -o runTestScript runTestScript.c

CMD ["./runTestScript"]


