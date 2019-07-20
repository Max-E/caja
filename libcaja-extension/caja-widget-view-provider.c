/* vi: set sw=4 ts=4 wrap ai: */
/*
 * caja-widget-view-provider.c: This file is part of ____
 *
 * Copyright (C) 2019 yetist <yetist@yetipc>
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * */

#include <config.h>
#include "caja-widget-view-provider.h"

#include <glib-object.h>

/**
 * SECTION:caja-widget-view-provider
 * @title: CajaWidgetViewProvider
 * @short_description: Interface to provide widgets view.
 * @include: libcaja-extension/caja-widget-view-provider.h
 *
 * #CajaWidgetViewProvider allows extension to provide widgets view
 * in the file manager.
 */

static void
caja_widget_view_provider_base_init (gpointer g_class)
{
}

GType
caja_widget_view_provider_get_type (void)
{
    static GType type = 0;

    if (!type) {
        const GTypeInfo info = {
            sizeof (CajaWidgetViewProviderIface),
            caja_widget_view_provider_base_init,
            NULL,
            NULL,
            NULL,
            NULL,
            0,
            0,
            NULL
        };

        type = g_type_register_static (G_TYPE_INTERFACE,
                                       "CajaWidgetViewProvider",
                                       &info, 0);
        g_type_interface_add_prerequisite (type, G_TYPE_OBJECT);
    }

    return type;
}

/**
 * caja_widget_view_provider_get_widget:
 * @provider: a #CajaWidgetViewProvider
 * @uri: the URI of the location
 * @window: parent #GtkWindow
 *
 * Returns: (transfer none): the widget view for @provider at @uri
 */

GtkWidget *
caja_widget_view_provider_get_widget (CajaWidgetViewProvider *provider)
{
    g_return_val_if_fail (CAJA_IS_WIDGET_VIEW_PROVIDER (provider), NULL);
    g_return_val_if_fail (CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->get_widget != NULL, NULL);

    return CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->get_widget (provider);
}

void caja_widget_view_provider_add_file (CajaWidgetViewProvider *provider, CajaFile *file)
{
    g_return_if_fail (CAJA_IS_WIDGET_VIEW_PROVIDER (provider));
    g_return_if_fail (CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->add_file != NULL);

    CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->add_file (provider, file);
}

void caja_widget_view_provider_set_uri (CajaWidgetViewProvider *provider, const char *uri)
{
    g_return_if_fail (CAJA_IS_WIDGET_VIEW_PROVIDER (provider));
    g_return_if_fail (CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->set_uri != NULL);

    CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->set_uri (provider, uri);
}

void caja_widget_view_provider_set_window (CajaWidgetViewProvider *provider, GtkWindow *window)
{
    g_return_if_fail (CAJA_IS_WIDGET_VIEW_PROVIDER (provider));
    g_return_if_fail (CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->set_window != NULL);

    CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->set_window (provider, window);
}


gboolean caja_widget_view_provider_supports_uri (CajaWidgetViewProvider *provider,
                                        const char *uri,
                                        GFileType file_type,
                                        const char *mime_type)
{
    g_return_val_if_fail (CAJA_IS_WIDGET_VIEW_PROVIDER (provider), FALSE);
    g_return_val_if_fail (CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->supports_uri!= NULL, FALSE);

    return CAJA_WIDGET_VIEW_PROVIDER_GET_IFACE (provider)->supports_uri (provider, uri, file_type, mime_type);
}
