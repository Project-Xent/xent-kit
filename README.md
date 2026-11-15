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

## Language bindings

The binding surface is the imperative API: `xtk_scene_*`, `xtk_txn_*`,
`xtk_ctrl_*`, `xtk_catalog_*` and event subscription. Declarative layers are
written per language on top of it; the C declarative runtime (`xtk_rt`) is one
such consumer, not part of the surface. Official bindings: oxent (Rust),
zxent (Zig), xenthon (Python), hsxent (Haskell).

- Enums crossing the ABI are four bytes (`static_assert`ed); bind them as
  `int32`. Public structs contain no `long double`, `__int128` or bit-fields.
- `static inline` helpers and function-like macros are not exported and carry
  no semantics of their own; reimplement them or fill the structs directly:
  `xtk_ref_none/existing/local`, `xtk_msg`, `xtk_msg_i`, `xtk_color_*`,
  `xtk_date`, `xtk_changestamp_valid`, `xtk_event_phasesvalid`,
  `xtk_utf8_len`, `xtk_ctrl_islist`, `xtk_ctrl_iscomp`, `xtk_kids`.
  `XTK_END` is the address `1`.
- The component ABI (`XtkCompType`, `xtk_component`, `xtk_comp_*`,
  `flux_host_registercomp`) is not part of the binding surface in 0.3.x and may
  change without notice.
- `xmake gen-bindings <rust|zig|cython|haskell|enum-types> <out>` generates
  typed control builders and enums from `tools/catalog.lua`.
- Register controls before the first commit: `flux_controls_use(&flux_ctrl_<name>)`
  (the name is the lowercase `XTK_CTRL_` suffix) or `flux_controls_all()`.
  Bindings whose builders are compiled only when used (oxent, zxent) register
  per builder so unused controls are not linked.
- Link a release bundle (`xent-<ver>-<arch>-windows-gnu.zip` from fluxent's
  `xmake dist`): `libxent.a` plus the system libraries in `lib/pkgconfig/xent.pc`.

## Dependencies

- [`xent-core`](https://github.com/Project-Xent/xent-core)

## License

0BSD
