---
layout: default
title: Architecture
---

# SpaceGame Architecture

## Engine layers

```mermaid
flowchart TB
    Gen[Procedural ship generator] --> Vox[Voxel model<br/>hull / engines / thrusters / weapons / armor]
    Vox --> Ren[Voxel renderer - SDL3]
    Cam[Camera - WASD + rotation] --> Ren
    Ren --> Frame[Rendered frame]
```
