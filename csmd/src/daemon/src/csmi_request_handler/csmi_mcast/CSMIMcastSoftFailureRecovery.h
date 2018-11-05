/*================================================================================

    csmd/src/daemon/src/csmi_request_handler/csmi_mcast/CSMIMcastSoftFailureRecovery.h

  © Copyright IBM Corporation 2015-2018. All Rights Reserved

    This program is licensed under the terms of the Eclipse Public License
    v1.0 as published by the Eclipse Foundation and available at
    http://www.eclipse.org/legal/epl-v10.html

    U.S. Government Users Restricted Rights:  Use, duplication or disclosure
    restricted by GSA ADP Schedule Contract with IBM Corp.
 
================================================================================*/

/**
 * @file CSMIMcastSoftFailureRecovery.h
 * @author John Dunham (jdunham@us.ibm)
 */

#ifndef CSMI_MCAST_SOFT_FAILURE_RECOVERY 
#define CSMI_MCAST_SOFT_FAILURE_RECOVERY

#include "CSMIMcast.h"
#include "csmi/include/csmi_type_wm_funct.h"
#include "csmi/include/csm_api_macros.h"
#include "csmi/src/wm/include/csmi_wm_type_internal.h" 
//#include <map>

#define STRUCT_TYPE csmi_soft_failure_recovery_context_t

struct csmi_soft_failure_recovery_context_t {
    uint32_t num_nodes;
    char**   compute_nodes;

    csmi_soft_failure_recovery_context_t() : num_nodes(0), compute_nodes(nullptr) {}

    ~csmi_soft_failure_recovery_context_t()
    {
        if (compute_nodes != nullptr &&  num_nodes > 0 )
        {
            for (uint32_t i = 0; i < num_nodes; ++i) free(compute_nodes[i]);
        }
        compute_nodes = nullptr;
    }

    void initNodes (uint32_t node_count)
    {
        num_nodes = node_count;
        compute_nodes = (char**)calloc(node_count, sizeof(char*));
    }
};

/** @brief Frees the @ref _Data structure if not null.
 * @tparam DataStruct The allocation create/delete/update multicast context.
 */
template<>
CSMIMcast<STRUCT_TYPE>::~CSMIMcast();

/** @brief Builds a specialized payload to handle allocation create/delete multicast payloads.
 *
 * @tparam DataStruct The allocation create/delete/update multicast context.
 *
 * @param[out] buffer The payload of the message to send to the compute agents.
 * @param[out] bufferLength The length of the @p bufferLength payload.
 */
template<>
void CSMIMcast<STRUCT_TYPE>::BuildMcastPayload(char** buffer, uint32_t* bufferLength);

/**
 * @brief Generates a unique identifier string for the mcast object.
 * Reports Allocation Id, Primary Job Id and Secondary Job Id.
 *
 * @return A string containing the unique identifier for the multicast.
 */
template<>
std::string CSMIMcast<STRUCT_TYPE>::GenerateIdentifierString();

/** @brief A typedef for @ref csmi_allocation_mcast_context_t specializations of @ref CSMIMcast.
 */
typedef CSMIMcast<STRUCT_TYPE> CSMIMcastSoftFailureRecovery;

namespace csm{
namespace mcast{
namespace nodes{
/** @brief Parses a message payload for Soft Failure events.
 *
 * The Parse operation saves values to @ref CSMIMcastSoftFailureRecovery::_Data.
 *
 * @param[in,out] mcastProps The properties of the multicast.
 * @param[in] content The message payload being parsed.
 *  
 * @return True if the response is valid.
 */
bool ParseResponseSoftFailure(CSMIMcastSoftFailureRecovery* mcastProps,
    const csm::network::MessageAndAddress content);
}
}
}

#undef STRUCT_TYPE
#endif
