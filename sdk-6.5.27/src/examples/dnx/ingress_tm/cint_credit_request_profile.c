/** file cint_credit_request_profile.c
 *  Used as an application reference to users to manage credit request profiles
 */
/*
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenBCM/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2022 Broadcom Inc. All rights reserved.
 */
/**
 * \brief - create the following fixed profiles for backward compatibility with legacy devices.
 *          For new applications it is recommended to follow the instructions in BCM88690 programmer guide
 */
int
cint_credit_request_profile_backward_compatibilty_set(int unit, int remote_credit_size)
{

    int slow_enabled_profiles[] = {BCM_COSQ_DELAY_TOLERANCE_10G_SLOW_ENABLED, BCM_COSQ_DELAY_TOLERANCE_40G_SLOW_ENABLED, BCM_COSQ_DELAY_TOLERANCE_100G_SLOW_ENABLED, BCM_COSQ_DELAY_TOLERANCE_200G_SLOW_ENABLED};
    int slow_disabled_profiles[] = {BCM_COSQ_DELAY_TOLERANCE_10G_LOW_DELAY, BCM_COSQ_DELAY_TOLERANCE_40G_LOW_DELAY, BCM_COSQ_DELAY_TOLERANCE_100G_LOW_DELAY, BCM_COSQ_DELAY_TOLERANCE_200G_LOW_DELAY};
    int profiles_rate[] = {10, 40, 100, 200};
    int profile_index;
    bcm_cosq_delay_tolerance_preset_attr_t credit_request_attr;
    bcm_cosq_delay_tolerance_t credit_request_profile;
    int profile_is_rate_class = *dnxc_data_get(unit, "iqs", "credit", "profile_is_rate_class", NULL);

    if (profile_is_rate_class)
    {
        printf("cint_credit_request_profile_backward_compatibilty_set is not supported for this device \n");
        return BCM_E_FAIL;
    }
    /** create slow enabled profiles */
    bcm_cosq_delay_tolerance_preset_attr_t_init(&credit_request_attr);

    credit_request_attr.credit_size = remote_credit_size; /** assume symmetric system */
    credit_request_attr.flags = BCM_COSQ_DELAY_TOLERANCE_PRESET_ATTR_F_SLOW_ENABLED;
    for (profile_index = 0; profile_index < 4; profile_index++)
    {
        /** get set of recommended values */
        credit_request_attr.rate = profiles_rate[profile_index];
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_delay_tolerance_preset_get(unit, &credit_request_attr, &credit_request_profile), "");
        /** set the threshold */
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_delay_tolerance_level_set(unit, slow_enabled_profiles[profile_index], &credit_request_profile), "");
    }

    /** create low delay profiles */
    bcm_cosq_delay_tolerance_preset_attr_t_init(&credit_request_attr);

    credit_request_attr.credit_size = remote_credit_size; /** assume symmetric system */
    for (profile_index = 0; profile_index < 4; profile_index++)
    {
        /** get set of recommended values */
        credit_request_attr.rate = profiles_rate[profile_index];
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_delay_tolerance_preset_get(unit, &credit_request_attr, &credit_request_profile), "");
        /** set the threshold */
        BCM_IF_ERROR_RETURN_MSG(bcm_cosq_delay_tolerance_level_set(unit, slow_disabled_profiles[profile_index], &credit_request_profile), "");
    }

    return BCM_E_NONE;
}

