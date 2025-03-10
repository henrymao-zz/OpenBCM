/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 *
 */

#include <sal/types.h>

#ifndef _LIF_PHASES_PRE_COMPILED_AUTO_GENERATED_XML_PARSER_H
#define _LIF_PHASES_PRE_COMPILED_AUTO_GENERATED_XML_PARSER_H
/* *INDENT-OFF* */

/**
 * \brief get handle for top node inside XML file or in a pre compiled string.
 * \par DIRECT INPUT
 *   \param [in] unit - Unit.
 *   \param [in] filepath - full path, either relative or absolute for XML file
 *   \param [in] topname - name of top XML node
 *   \param [in] flags - options for file opening, see above CONF_OPEN_*
 * \par DIRECT OUTPUT:
 *   \retval xml_node if XML file exists and has top node with this name
 *   \retval NULL for any failure
 */
void *dbx_pre_compiled_lif_phases_top_get(
    int unit,
    char *filepath,
    char *topname,
    int flags);

/* *INDENT-ON* */
#endif /* _LIF_PHASES_PRE_COMPILED_AUTO_GENERATED_XML_PARSER_H */
