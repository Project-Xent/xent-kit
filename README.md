# xent-kit

Platform-agnostic declarative UI toolkit for the Xent framework, written in C17.
xent-kit provides the Elm-architecture runtime, virtual DOM reconciler, and element
API that all Xent backends share.

## Architecture

- **Element layer** (`xtk_el.h`) — declarative element constructors (`xtk_button`,
  `xtk_text`, `xtk_column`, etc.) that build a per-frame element tree on an arena.
- **Reconciler** (`xtk_reconcile.h`) — diffs the previous and current element trees,
  mounts/unmounts/reorders nodes through an `XtkBackend` vtable, and patches props
  in place. Supports keyed identity for stable reorder.
- **Runtime** (`xtk_runtime.h`) — message queue, frame pump, and the Elm update/view
  loop. Backends call `xtk_runtime_frame()` each frame; the runtime drains messages,
  calls `update`, rebuilds the view, and reconciles.
- **Backend vtable** (`XtkBackend`) — 9 function pointers that a platform backend
  implements: `create`, `destroy`, `apply_props`, `mount_setup`, `is_interactive`,
  `request_frame`, `pre_unmount`, `node_cleanup`, `binding_create`. Write it once in
  xent-kit, implement it per platform.

## Backends

| Backend | Platform | Repo |
|---------|----------|------|
| fluxent | Windows (D3D11/D2D/DComp) | [fluxent](https://github.com/Project-Xent/fluxent) |

## Build

```bash
xmake                    # build library + tests
xmake run test_xtk_el    # run element layer tests
```

Requires a C17 compiler and `xmake`.

## Dependencies

- [`xent-core`](https://github.com/Project-Xent/xent-core)

## License

0BSD
