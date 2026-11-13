# Migrating xent-kit code to 0.3

Backend implementations now provide an `XtkHostVtable`. Mutations arrive as one
validated `XtkBatch` and follow `preflight -> prepare -> commit`, or `abort`.
Do not mutate a live backend tree while planning a declarative update.

Imperative code creates an `XtkScene` over the same Host and uses generated
typed control functions or direct batch operations. Declarative code still
builds `XtkEl` trees, but the reconciler is only a client of that public Host
protocol.

Sibling identity must be uniformly positional or uniformly keyed. Use
`xtk_keyed` for diagnostic string keys and `xtk_keyed_u64` for allocation-free
numeric identity. Duplicate or mixed keys are rejected.

Replace custom-control/backend callback extensions with an `XtkCompType`.
Fallible mount and update work belongs in `prepare_mount` or `prepare_update`;
commit cannot fail, abort releases preparation, and unmount releases retained
state. Platform capabilities are typed `XtkProviderDesc` entries scoped to the
Scene.

List-specific runtime viewport hooks are gone. Hosts expose the general
viewport/virtual-range contract, and virtualized elements declare the range
they realize.
