# warehouse-simulator

The main goal of this project is to develop a networked control system for a warehouse.

# Installation

System Requirements:
    - Linux kernel version 6.1.0

Dependencies:
    - Podman version 3.4.4

Instructions:
``` Bash
# clone the repository
git clone https://github.com/brycethebjorkman/warehouse-simulator

# clone submodules
cd warehouse-simulator
git submodule update --init --recursive
```

# Usage

``` Bash
# use the dev script to build and enter the container
./dev --build

# then within the container run the simulation
bash run-warehouse

# after the simulation completes (default time 120s) retrieve results from another shell
podman cp warehouse-simulator:/usr/app/results .
```

# Design Requirements

## Initial
- warehouse will receive packages as inputs and produce packages as outputs
- warehouse will mainly be composed of a sortation system and an automated storage and retrieval system
- control system will receive high-level commands as reference inputs, and interact with the sortation system and the automated storage and retrieval system
- network connecting the different computer systems of this warehouse will be an implementation of IEEE Time-Sensitive Networking
- concepts from the course:
    - timed models
    - dynamical systems
    - safety requirements
    - liveness requirements
## Intermediate
- first release aims to provide some default schedules that can be selected on simulation invocation
- for seeing the results of system execution, a console log will be used for first release
## Elicited
- safety monitor
- modeling interfaces
- component architecture diagram
- timing assumptions (e.g. time resolution)

# Model Assumptions
- Pallet base dimensions are the typical 40" x 48"
- Pallet Weight and Dimensions are all valid
- Pallet Queue size for Shipment and Order is in [1,52]
    - a standard 53' x 8.5' trailer is the largest common flat bed size, which could potentially fit 2 layers of 2 rows of 13 Pallets
- Orders care about Pallet Product Type, not specific Pallet ID
- Pallet loading and unloading are "instantaneous" as soon as the Gate is cleared (so no backups will occur)
- Motion Controller components support linear interpolation and inertia compensation

# Simulation
Global Data:
- Pallet:
    - ID
    - Product Type

Global State:
- Shipment Table:
    - Gate ID
    - Pallet Queue
- Storage Table:
    - Slot ID
    - Pallet
- Order Table:
    - Gate ID
    - Pallet Queue

Global Input:
- Received Shipment Table:
    - Arrival Time
    - Gate ID
    - Pallet Queue
- Placed Order Table:
    - Placement Time
    - Gate ID
    - Pallet Queue

Global Output:
- Completed Order Table:
    - Gate ID
    - Load Table:
        - Pallet ID
        - Load Time
