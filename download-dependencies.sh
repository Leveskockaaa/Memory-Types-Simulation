#!/bin/bash

echo "Updating package list..."
sudo apt update

echo "Installing build-essential package..."
sudo apt install -y build-essential
