// This C++ source file was generated by the TTCN-3 compiler
// of the TTCN-3 Test Executor version CRL 113 200/6 R4A
// for dark (dark@development) on Thu Jun  7 12:56:12 2018

// Copyright (c) 2000-2018 Ericsson Telecom AB

// Do not edit this file unless you know what you are doing.

/* Including header files */

#include "ServiceProfiling_Testcases.hh"

namespace ServiceProfiling__Testcases {

/* Prototypes of static functions */

static void pre_init_module();
static void post_init_module();
static void module_control_part();

/* Literal string constants */

static const unsigned char module_checksum[] = { 0xec, 0xa2, 0x49, 0x3b, 0xdb, 0x75, 0xef, 0xa9, 0x35, 0x7a, 0x4f, 0xf7, 0x10, 0xf5, 0x05, 0x66 };

/* Global variable definitions */

TTCN_Module module_object("ServiceProfiling_Testcases", __DATE__, __TIME__, module_checksum, pre_init_module, NULL, 0U, 4294967295U, 4294967295U, 4294967295U, NULL, 0LU, 0, post_init_module, NULL, NULL, NULL, NULL, NULL, NULL, module_control_part);

static const RuntimeVersionChecker ver_checker(  current_runtime_version.requires_major_version_6,
  current_runtime_version.requires_minor_version_4,
  current_runtime_version.requires_patch_level_0,  current_runtime_version.requires_runtime_1);

/* Bodies of functions, altsteps and testcases */

verdicttype testcase_SimpleServiceProfiling(const ServiceProfiling__Types::ServiceProfilingExperiment_template& spe, boolean has_timer, double timer_value)
{
TTCN_Runtime::check_begin_testcase(has_timer, timer_value);
try {
TTCN_Runtime::begin_testcase("ServiceProfiling_Testcases", "SimpleServiceProfiling", "ServiceProfiling_PortType", "MANO", "ServiceProfiling_PortType", "MANO", has_timer, timer_value);
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 9 */
TTCN_Runtime::map_port(MTC_COMPREF, ServiceProfiling__PortType::MANO_component_Port.get_name(), SYSTEM_COMPREF, ServiceProfiling__PortType::MANO_component_Port.get_name());
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 11 */
ServiceProfiling__Types::Setup__SFC_template setup__sfc__req;
setup__sfc__req.service__name() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).service__name();
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 12 */
ServiceProfiling__PortType::MANO_component_Port.send(setup__sfc__req);
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 14 */
ServiceProfiling__Types::Add__VNF_template add__vnf__request1;
add__vnf__request1.name() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).MpVNFs()[0].name();
add__vnf__request1.connection__point() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).MpVNFs()[0].connection__point();
add__vnf__request1.image() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).MpVNFs()[0].image();
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 15 */
ServiceProfiling__PortType::MANO_component_Port.send(add__vnf__request1);
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 17 */
ServiceProfiling__Types::Add__VNF_template add__vnf__request2;
add__vnf__request2.name() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).MpVNFs()[1].name();
add__vnf__request2.connection__point() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).MpVNFs()[1].connection__point();
add__vnf__request2.image() = const_cast< const ServiceProfiling__Types::ServiceProfilingExperiment_template&>(spe).MpVNFs()[1].image();
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 18 */
ServiceProfiling__PortType::MANO_component_Port.send(add__vnf__request2);
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 22 */
TTCN_Runtime::setverdict(PASS);
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 23 */
TTCN_Runtime::stop_execution();
} catch (const TC_Error& tc_error) {
} catch (const TC_End& tc_end) {
TTCN_Logger::log_str(TTCN_FUNCTION, "Test case SimpleServiceProfiling was stopped.");
}
return TTCN_Runtime::end_testcase();
}


/* Bodies of static functions */

static void pre_init_module()
{
ServiceProfiling__PortType::module_object.pre_init_module();
ServiceProfiling__Functions::module_object.pre_init_module();
ServiceProfiling__Templates::module_object.pre_init_module();
module_object.add_testcase_pard("SimpleServiceProfiling", (genericfunc_t)&testcase_SimpleServiceProfiling);
}

static void post_init_module()
{
ServiceProfiling__PortType::module_object.post_init_module();
ServiceProfiling__Functions::module_object.post_init_module();
ServiceProfiling__Templates::module_object.post_init_module();
}

static void module_control_part()
{
TTCN_Runtime::begin_controlpart("ServiceProfiling_Testcases");
/* /home/dark/eclipse-workspace/nfv-service-profiling/src/ServiceProfiling_Testcases.ttcn, line 27 */
testcase_SimpleServiceProfiling(ServiceProfiling__Templates::spexperiment, FALSE, 0.0);
TTCN_Runtime::end_controlpart();
}


} /* end of namespace */
