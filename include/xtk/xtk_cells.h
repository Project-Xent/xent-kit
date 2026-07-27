#ifndef XTK_CELLS_H
#define XTK_CELLS_H

#include "xtk_scene.h"

typedef struct XtkCells XtkCells;
typedef uint32_t        XtkCellId;

#define XTK_CELL_INVALID (( XtkCellId ) UINT32_MAX)

typedef enum XtkCellAccept
{
	XTK_CELL_ACCEPTED,
	XTK_CELL_ECHO,
	XTK_CELL_REJECTED,
} XtkCellAccept;

/* Restricted same-thread bindings for Component-owned stable leaf controls.
 * A set accepts TEXT, VALUE_F32, and VALUE_F64 only. Dirty values share one
 * standard Host batch; a failed flush preserves them for retry. */
XtkCells     *xtk_cells_create(XtkScene scene, XtkSourceId source);
bool          xtk_cells_destroy(XtkCells *cells);
XtkCellId     xtk_cells_bind(XtkCells *cells, XtkCtrl target, XtkPropertyId property);

bool          xtk_cell_set_f32(XtkCells *cells, XtkCellId cell, float value);
bool          xtk_cell_set_f64(XtkCells *cells, XtkCellId cell, double value);
bool          xtk_cell_set_string(XtkCells *cells, XtkCellId cell, char const *data, uint32_t len);
bool          xtk_cells_flush(XtkCells *cells);

XtkCellAccept xtk_cell_accept(XtkCells *cells, XtkCellId cell, XtkValueView const *value, XtkChangeStamp change);
bool          xtk_cell_get(XtkCells const *cells, XtkCellId cell, XtkValueView *out);

#endif
