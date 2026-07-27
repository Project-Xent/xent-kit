# xent-kit

Project Xent's platform-neutral standard control protocol, retained Host, and
declarative runtime, written in C23. Imperative code and declarative views use
the same control descriptors, properties, events, handles, and atomic batches.

## Architecture

- `xtk_descriptor.h` and `xtk_catalog.h` define the standard control/property/
  event vocabulary.
- `xtk_batch.h` is the mutation wire format. A Host validates, prepares, and
  atomically commits one batch or leaves the live tree unchanged.
- `xtk_host.h` is the retained Host ABI. `xtk_scene.h` and the generated
  `xtk_controls.h` provide typed imperative conveniences over it.
- `xtk.h` builds transient declarative element trees. The reconciler emits only
  public `XtkBatch` operations and publishes its new composition after commit.
- `xtk_msg.h` supplies the bounded message/update/view runtime. Messages drain
  before one build/reconcile/commit per frame.
- `xtk_component.h` defines transactional Components and typed, Scene-scoped
  Providers. Component state belongs to the Host, not the transient tree.

Sibling identity is either positional or keyed. String keys remain useful for
diagnostics; `xtk_keyed_u64` provides allocation-free scalar identity. Keyed
matching is O(n), reuses retained capacity, and emits ordered moves.

Virtualization is a control-neutral retained-region contract: the runtime asks
the Host for a viewport and publishes the realized range. ListView, GridView,
ItemsView, and custom Components can share that seam without a list-specific
Host ABI.

## Backends

| Backend | Platform | Repo |
|---------|----------|------|
| fluxent | Windows (D3D11/D2D/DComp) | [fluxent](https://github.com/Project-Xent/fluxent) |

## Build

```sh
xmake
xmake test
xmake run test_xtk_reconcile_txn
```

The test gate includes Host atomicity, allocation failures, Components,
Providers, generated catalog coverage, event routing, virtualization,
reconciliation, and static/revisioned regions.

## Dependencies

- [`xent-core`](https://github.com/Project-Xent/xent-core)

## License

0BSD
