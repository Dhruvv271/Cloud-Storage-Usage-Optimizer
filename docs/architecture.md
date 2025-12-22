# System Architecture

## Overview
This project implements a real-time cloud storage usage optimization system.
It ingests storage access events, processes them using a C++ analytics engine,
and exposes metrics and optimization recommendations via a dashboard.

## High-Level Flow

Storage Events → Analytics Engine → REST API → Dashboard

## Components

### 1. Event Simulator
Simulates cloud storage events such as file upload, read, and delete.

### 2. Analytics Engine (C++)
Processes events in real time and maintains:
- Storage usage metrics
- File access frequency
- Hot vs cold file classification

### 3. API Server
Exposes analytics and optimization data via REST endpoints.

### 4. Dashboard
Displays live metrics and optimization suggestions.

## Design Goals
- Low-latency event processing
- Simple, extensible architecture
- Clear separation of concerns
