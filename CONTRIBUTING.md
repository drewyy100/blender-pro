# Contributing to Blender Pro

## Code Style

```cpp
// Classes: PascalCase
class MeshData { };

// Functions/variables: camelCase
void processMesh(const Mesh& mesh);
int vertexCount = 0;

// Constants: UPPER_SNAKE_CASE
const int MAX_VERTICES = 1000000;

// Files: snake_case
mesh_data.hpp
```

## Commit Messages

- Use present tense
- Be specific
- Reference issues: "Fixes #123"

## Pull Requests

1. One feature per PR
2. Include tests
3. Update documentation
4. Pass all CI checks

## Testing

Minimum 80% code coverage required.

```bash
cmake --build . --target test
```
