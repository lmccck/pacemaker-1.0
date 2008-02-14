/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.iterate.conf,v 5.9 2003/06/04 00:14:41 hardaker Exp $
 */

#include <crm_internal.h>


#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include "LHAResourceTable.h"

#include "hbagent.h"
#include "hbagentv2.h"
#include "hb_api.h"
/*#include "heartbeat.h"*/
/*#include "clplumbing/cl_log.h"*/

static GPtrArray * gResourceTableV2 = NULL;
extern const int snmp_cache_time_out;

static int LHAResourceTable_load(netsnmp_cache *cache, void *vmagic); 
static void LHAResourceTable_free(netsnmp_cache *cache, void *vmagic); 

/** Initialize the LHAResourceTable table by defining its contents and how it's structured */
void
initialize_table_LHAResourceTable(void)
{
    static oid      LHAResourceTable_oid[] = { 1, 3, 6, 1, 4, 1, 4682, 8 };
    netsnmp_table_registration_info *table_info;
    netsnmp_handler_registration *my_handler;
    netsnmp_iterator_info *iinfo;

    /** create the table registration information structures */
    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    iinfo = SNMP_MALLOC_TYPEDEF(netsnmp_iterator_info);

    /** if your table is read only, it's easiest to change the
        HANDLER_CAN_RWRITE definition below to HANDLER_CAN_RONLY */
    my_handler = netsnmp_create_handler_registration("LHAResourceTable",
                                                     LHAResourceTable_handler,
                                                     LHAResourceTable_oid,
                                                     OID_LENGTH
                                                     (LHAResourceTable_oid),
                                                     HANDLER_CAN_RONLY);

    if (!my_handler || !table_info || !iinfo) {
        snmp_log(LOG_ERR,
                 "malloc failed in initialize_table_LHAResourceTable");
        SNMP_FREE(iinfo);
        SNMP_FREE(table_info);
        return;                 /* Serious error. */
    }

    /***************************************************
     * Setting up the table's definition
     */
    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER,   /* index: LHAResourceIndex */
                                     0);

    /** Define the minimum and maximum accessible columns.  This
        optimizes retrival. */
    table_info->min_column = 2;
    table_info->max_column = 8;

    /*
     * iterator access routines 
     */
    iinfo->get_first_data_point = LHAResourceTable_get_first_data_point;
    iinfo->get_next_data_point = LHAResourceTable_get_next_data_point;

    /** you may wish to set these as well */
#ifdef MAYBE_USE_THESE
    iinfo->make_data_context = LHAResourceTable_context_convert_function;
    iinfo->free_data_context = LHAResourceTable_data_free;

    /** pick *only* one of these if you use them */
    iinfo->free_loop_context = LHAResourceTable_loop_free;
    iinfo->free_loop_context_at_end = LHAResourceTable_loop_free;
#endif

    /** tie the two structures together */
    iinfo->table_reginfo = table_info;

    /***************************************************
     * registering the table with the master agent
     */
    DEBUGMSGTL(("initialize_table_LHAResourceTable",
                "Registering table LHAResourceTable as a table iterator\n"));
    netsnmp_register_table_iterator(my_handler, iinfo);

    /*
     * enable local cache
     */
    netsnmp_inject_handler(my_handler,
               netsnmp_get_cache_handler(snmp_cache_time_out,
                             LHAResourceTable_load,
                             LHAResourceTable_free,
                             LHAResourceTable_oid,
                             OID_LENGTH
                             (LHAResourceTable_oid)));
                                 

    snmp_log(LOG_INFO,
             "LHAResourceTable initialization completed.\n");
}

/** Initializes the LHAResourceTable module */
void
init_LHAResourceTable(void)
{

  /** here we initialize all the tables we're planning on supporting */
    initialize_table_LHAResourceTable();
}

/** returns the first data point within the LHAResourceTable table data.

    Set the my_loop_context variable to the first data point structure
    of your choice (from which you can find the next one).  This could
    be anything from the first node in a linked list, to an integer
    pointer containing the beginning of an array variable.

    Set the my_data_context variable to something to be returned to
    you later (in your main LHAResourceTable_handler routine) that will provide
    you with the data to return in a given row.  This could be the
    same pointer as what my_loop_context is set to, or something
    different.

    The put_index_data variable contains a list of snmp variable
    bindings, one for each index in your table.  Set the values of
    each appropriately according to the data matching the first row
    and return the put_index_data variable at the end of the function.
*/
netsnmp_variable_list *
LHAResourceTable_get_first_data_point(void **my_loop_context,
                                      void **my_data_context,
                                      netsnmp_variable_list *
                                      put_index_data,
                                      netsnmp_iterator_info *mydata)
{
    if (gResourceTableV2 && gResourceTableV2->len == 0) {
        return NULL;
    }

    *my_loop_context = NULL;
    return LHAResourceTable_get_next_data_point(my_loop_context,
                                                my_data_context,
                                                put_index_data,
                                                mydata);
}

/** functionally the same as LHAResourceTable_get_first_data_point, but
   my_loop_context has already been set to a previous value and should
   be updated to the next in the list.  For example, if it was a
   linked list, you might want to cast it to your local data type and
   then return my_loop_context->next.  The my_data_context pointer
   should be set to something you need later (in your main
   LHAResourceTable_handler routine) and the indexes in put_index_data updated
   again. */
netsnmp_variable_list *
LHAResourceTable_get_next_data_point(void **my_loop_context,
                                     void **my_data_context,
                                     netsnmp_variable_list *
                                     put_index_data,
                                     netsnmp_iterator_info *mydata)
{
    static size_t i = 0;
    netsnmp_variable_list *vptr;
    struct hb_rsinfov2 *info;

    if (*my_loop_context != NULL) {
        i = *((size_t *) *my_loop_context);
    } else {
        i = 0;
    }

    if (!gResourceTableV2 || i >= gResourceTableV2->len) {
        return NULL;
    }

    vptr = put_index_data;
    info = (struct hb_rsinfov2 *)g_ptr_array_index(gResourceTableV2, i);

    snmp_set_var_value(vptr, (u_char *)&info->index, sizeof(size_t));
    vptr = vptr->next_variable;

    i++;
    *my_loop_context = (void *)&i;
    *my_data_context = (void *)info;
    
    return put_index_data;
}

/** handles requests for the LHAResourceTable table, if anything else needs to be done */
int
LHAResourceTable_handler(netsnmp_mib_handler *handler,
                         netsnmp_handler_registration *reginfo,
                         netsnmp_agent_request_info *reqinfo,
                         netsnmp_request_info *requests)
{

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    netsnmp_variable_list *var;

    struct hb_rsinfov2 *entry;

    for (request = requests; request; request = request->next) {
        var = request->requestvb;
        if (request->processed != 0)
            continue;

        /** perform anything here that you need to do before each
           request is processed. */

        /** the following extracts the my_data_context pointer set in
           the loop functions above.  You can then use the results to
           help return data for the columns of the LHAResourceTable table in question */
        entry = 
            (struct hb_rsinfov2 *)netsnmp_extract_iterator_context(request);
        if (entry == NULL) {
            if (reqinfo->mode == MODE_GET) {
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHINSTANCE);
                continue;
            }
            /** XXX: no row existed, if you support creation and this is a
               set, start dealing with it here, else continue */
        }

        /** extracts the information about the table from the request */
        table_info = netsnmp_extract_table_info(request);
        /** table_info->colnum contains the column number requested */
        /** table_info->indexes contains a linked list of snmp variable
           bindings for the indexes of the table.  Values in the list
           have been set corresponding to the indexes of the
           request */
        if (table_info == NULL) {
            continue;
        }

        switch (reqinfo->mode) {
            /** the table_iterator helper should change all GETNEXTs
               into GETs for you automatically, so you don't have to
               worry about the GETNEXT case.  Only GETs and SETs need
               to be dealt with here */
        case MODE_GET:
            switch (table_info->colnum) {
            case COLUMN_LHARESOURCENAME:
                snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                         (u_char *)entry->resourceid,
                                         strlen(entry->resourceid) + 1
                                         );
                break;

            case COLUMN_LHARESOURCETYPE:
                snmp_set_var_typed_value(var, ASN_INTEGER,
                                         (u_char *)&entry->type,
                                         sizeof(entry->type)
                                         );
                break;

            case COLUMN_LHARESOURCESTATUS:
                snmp_set_var_typed_value(var, ASN_INTEGER,
                                         (u_char *)&entry->status,
                                         sizeof(entry->status)
                                         );
                break;

            case COLUMN_LHARESOURCENODE:
                snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                         (u_char *)entry->node,
                                         strlen(entry->node) + 1
                                         );
                break;

            case COLUMN_LHARESOURCEISMANAGED:
                snmp_set_var_typed_value(var, ASN_INTEGER,
                                         (u_char *)&entry->is_managed,
                                         sizeof(entry->is_managed)
                                         );
                break;

            case COLUMN_LHARESOURCEFAILCOUNT:
                snmp_set_var_typed_value(var, ASN_INTEGER,
                                         (u_char *)&entry->failcount,
                                         sizeof(entry->failcount)
                                         );
                break;

            case COLUMN_LHARESOURCEPARENT:
                snmp_set_var_typed_value(var, ASN_OCTET_STR,
                                         (u_char *)entry->parent,
                                         strlen(entry->parent) + 1
                                         );
                break;

            default:
                        /** We shouldn't get here */
                snmp_log(LOG_ERR,
                         "problem encountered in LHAResourceTable_handler: unknown column\n");
            }
            break;

        case MODE_SET_RESERVE1:
                /** set handling... */

        default:
            snmp_log(LOG_ERR,
                     "problem encountered in LHAResourceTable_handler: unsupported mode\n");
        }
    }
    return SNMP_ERR_NOERROR;
}

static int LHAResourceTable_load(netsnmp_cache *cache, void *vmagic)
{
    LHAResourceTable_free(cache, vmagic);

    gResourceTableV2 = get_resource_table_v2();

    return 0;
}

static void LHAResourceTable_free(netsnmp_cache *cache, void *vmagic)
{
    /* do nothing. */
    return;
}



/**
 * Emacs stuff:
 * Local Variables:
 * mode: C
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 *
 */
