/*================================================================================
   
    csmi/src/common/include/csmi_common_type_internal.h

    © Copyright IBM Corporation 2015-2017. All Rights Reserved

    This program is licensed under the terms of the Eclipse Public License
    v1.0 as published by the Eclipse Foundation and available at
    http://www.eclipse.org/legal/epl-v10.html
    
    U.S. Government Users Restricted Rights:  Use, duplication or disclosure
    restricted by GSA ADP Schedule Contract with IBM Corp.
    
================================================================================*/
#ifndef _CSMI_COMMON_TYPE_INTERNAL_H_
#define _CSMI_COMMON_TYPE_INTERNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "csmi/include/csmi_type_common.h"
/**
 * @brief A container for a CSM error, encapsulates the source error code and message.
 */
typedef struct {
    uint64_t _metadata; /** The number of fields in the struct.*/
    int errcode; ///< The error code of this error message. 
    char* errmsg; ///< The error message. 
    char* source; ///< The host reporting the error.
} csm_node_error_t;
 /**  @brief Serializes the supplied structure into a char buffer.
*
* @param[in]  target     The structure to pack into the char buffer.
* @param[out] buf        Contains the structure as char buffer.
* @param[out] buffer_len Contains the length of the buffer.
*/
int serialize_csm_node_error_t( csm_node_error_t *target, char **buf , uint32_t *buffer_len);

/** @brief Deserializes the supplied character buffer.
*
* @param[out] dest       A pointer to a struct to output the contents of the buffer to.
* @param[in]  buffer     The buffer to read into the destination struct.
* @param[in]  buffer_len The size of the buffer provided (for overflows).
*/
int deserialize_csm_node_error_t( csm_node_error_t **dest, const char *buffer, uint32_t buffer_len);

/** @brief Frees the supplied struct and its members.
*
*  @warning Don't invoke unless @p target has been initialized by the init function.
*
*  @param[in] target The struct to free.
*/
void free_csm_node_error_t( csm_node_error_t *target );

/** @brief Initializes the supplied struct to the default values.
*
*  @param[in,out] target The struct to initialize.
*/
void init_csm_node_error_t( csm_node_error_t *target );


/**
 * @brief An internal container for a CSM error, encapsulates the error code, message and error list.
 */
typedef struct {
    uint64_t _metadata; /** The number of fields in the struct.*/
    int errcode; ///< The error code of this error message.
    char* errmsg; ///< The error message.
    uint32_t error_count; ///< A count of errors. 
    csm_node_error_t** node_errors; ///< Collection of errors which occured on nodes.
} csmi_err_t;
 /**  @brief Serializes the supplied structure into a char buffer.
*
* @param[in]  target     The structure to pack into the char buffer.
* @param[out] buf        Contains the structure as char buffer.
* @param[out] buffer_len Contains the length of the buffer.
*/
int serialize_csmi_err_t( csmi_err_t *target, char **buf , uint32_t *buffer_len);

/** @brief Deserializes the supplied character buffer.
*
* @param[out] dest       A pointer to a struct to output the contents of the buffer to.
* @param[in]  buffer     The buffer to read into the destination struct.
* @param[in]  buffer_len The size of the buffer provided (for overflows).
*/
int deserialize_csmi_err_t( csmi_err_t **dest, const char *buffer, uint32_t buffer_len);

/** @brief Frees the supplied struct and its members.
*
*  @warning Don't invoke unless @p target has been initialized by the init function.
*
*  @param[in] target The struct to free.
*/
void free_csmi_err_t( csmi_err_t *target );

/** @brief Initializes the supplied struct to the default values.
*
*  @param[in,out] target The struct to initialize.
*/
void init_csmi_err_t( csmi_err_t *target );



#ifdef __cplusplus
}
#endif
#endif
