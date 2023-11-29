#
# Copyright 2021-2023 Software Radio Systems Limited
#
# By using this file, you agree to the terms and conditions set
# forth in the LICENSE file which can be found at the top level of
# the distribution.
#

"""
Test ping
"""
import logging
from contextlib import suppress
from typing import Optional, Sequence, Union

import grpc
from _pytest.outcomes import Failed
from pytest import mark
from retina.client.manager import RetinaTestManager
from retina.launcher.artifacts import RetinaTestData
from retina.launcher.utils import configure_artifacts, param
from retina.protocol.base_pb2 import PLMN
from retina.protocol.fivegc_pb2_grpc import FiveGCStub
from retina.protocol.gnb_pb2_grpc import GNBStub
from retina.protocol.ue_pb2_grpc import UEStub

from .steps.configuration import configure_test_parameters, get_minimum_sample_rate_for_bandwidth
from .steps.stub import ping, start_network, stop, ue_start_and_attach, ue_stop


@mark.parametrize(
    "reattach_count",
    (
        param(0, id="reattach:%s"),
        param(2, id="reattach:%s", marks=mark.reattach),
    ),
)
@mark.parametrize(
    "band, common_scs, bandwidth",
    (
        param(3, 15, 10, id="band:%s-scs:%s-bandwidth:%s"),
        param(78, 30, 20, id="band:%s-scs:%s-bandwidth:%s"),
    ),
)
@mark.android
# pylint: disable=too-many-arguments
def test_android(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_1: UEStub,
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
    reattach_count: int,
):
    """
    Android Pings
    """

    _ping(
        retina_manager=retina_manager,
        retina_data=retina_data,
        ue_array=(ue_1,),
        gnb=gnb,
        fivegc=fivegc,
        band=band,
        common_scs=common_scs,
        bandwidth=bandwidth,
        sample_rate=get_minimum_sample_rate_for_bandwidth(bandwidth),
        global_timing_advance=-1,
        time_alignment_calibration="auto",
        warning_as_errors=False,
        always_download_artifacts=True,
        reattach_count=reattach_count,
    )


@mark.parametrize(
    "reattach_count",
    (
        param(0, id="reattach:%s"),
        param(2, id="reattach:%s", marks=mark.reattach),
    ),
)
@mark.parametrize(
    "band, common_scs, bandwidth",
    (
        param(7, 15, 20, id="band:%s-scs:%s-bandwidth:%s"),
        param(78, 30, 20, id="band:%s-scs:%s-bandwidth:%s"),
    ),
)
@mark.android_hp
# pylint: disable=too-many-arguments
def test_android_hp(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_1: UEStub,
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
    reattach_count: int,
):
    """
    Android high performance Pings
    """

    _ping(
        retina_manager=retina_manager,
        retina_data=retina_data,
        ue_array=(ue_1,),
        gnb=gnb,
        fivegc=fivegc,
        band=band,
        common_scs=common_scs,
        bandwidth=bandwidth,
        sample_rate=None,
        global_timing_advance=-1,
        time_alignment_calibration="auto",
        warning_as_errors=False,
        always_download_artifacts=True,
        reattach_count=reattach_count,
    )


@mark.parametrize(
    "band, common_scs, bandwidth",
    (
        param(3, 15, 5, id="band:%s-scs:%s-bandwidth:%s"),
        param(3, 15, 10, marks=mark.test, id="band:%s-scs:%s-bandwidth:%s"),
        param(3, 15, 20, id="band:%s-scs:%s-bandwidth:%s"),
        param(3, 15, 50, id="band:%s-scs:%s-bandwidth:%s"),
        param(41, 30, 10, id="band:%s-scs:%s-bandwidth:%s"),
        param(41, 30, 20, id="band:%s-scs:%s-bandwidth:%s"),
        param(41, 30, 50, id="band:%s-scs:%s-bandwidth:%s"),
    ),
)
@mark.zmq
# pylint: disable=too-many-arguments
def test_zmq(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_1: UEStub,
    ue_2: UEStub,
    ue_3: UEStub,
    ue_4: UEStub,
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
):
    """
    ZMQ Pings
    """

    _ping(
        retina_manager=retina_manager,
        retina_data=retina_data,
        ue_array=(ue_1, ue_2, ue_3, ue_4),
        gnb=gnb,
        fivegc=fivegc,
        band=band,
        common_scs=common_scs,
        bandwidth=bandwidth,
        sample_rate=None,  # default from testbed
        global_timing_advance=0,
        time_alignment_calibration=0,
    )


@mark.parametrize(
    "band, common_scs, bandwidth",
    (param(3, 15, 10, id="band:%s-scs:%s-bandwidth:%s"),),
)
@mark.zmq_valgrind
# pylint: disable=too-many-arguments
def test_zmq_valgrind(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_1: UEStub,
    ue_2: UEStub,
    ue_3: UEStub,
    ue_4: UEStub,
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
):
    """
    Valgrind Ping
    - Ignore if the ping fails or ue can't attach
    - Fails only if ue/gnb/5gc crashes
    """
    gnb_stop_timeout = 150
    with suppress(grpc.RpcError, AssertionError, Failed):
        _ping(
            retina_manager=retina_manager,
            retina_data=retina_data,
            ue_array=(ue_1, ue_2, ue_3, ue_4),
            gnb=gnb,
            fivegc=fivegc,
            band=band,
            common_scs=common_scs,
            bandwidth=bandwidth,
            sample_rate=None,  # default from testbed
            global_timing_advance=0,
            time_alignment_calibration=0,
            log_search=False,
            always_download_artifacts=True,
            pre_command="valgrind --leak-check=full --track-origins=yes --exit-on-first-error=no --error-exitcode=22",
            gnb_stop_timeout=gnb_stop_timeout,
        )
    stop(
        (ue_1, ue_2, ue_3, ue_4),
        gnb,
        fivegc,
        retina_data,
        gnb_stop_timeout=gnb_stop_timeout,
        log_search=False,
    )


@mark.parametrize(
    "band, common_scs, bandwidth",
    (
        param(3, 15, 10, id="band:%s-scs:%s-bandwidth:%s"),
        param(41, 30, 10, id="band:%s-scs:%s-bandwidth:%s"),
    ),
)
@mark.rf
# pylint: disable=too-many-arguments
def test_rf(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_1: UEStub,
    ue_2: UEStub,
    ue_3: UEStub,
    ue_4: UEStub,
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
):
    """
    RF Pings
    """

    _ping(
        retina_manager=retina_manager,
        retina_data=retina_data,
        ue_array=(ue_1, ue_2, ue_3, ue_4),
        gnb=gnb,
        fivegc=fivegc,
        band=band,
        common_scs=common_scs,
        bandwidth=bandwidth,
        sample_rate=None,  # default from testbed
        global_timing_advance=-1,
        time_alignment_calibration="auto",
        warning_as_errors=False,
        always_download_artifacts=True,
    )


@mark.parametrize(
    "band, common_scs, bandwidth",
    (param(3, 15, 10, id="band:%s-scs:%s-bandwidth:%s"),),
)
@mark.rf_not_crash
# pylint: disable=too-many-arguments
def test_rf_does_not_crash(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_1: UEStub,
    ue_2: UEStub,
    ue_3: UEStub,
    ue_4: UEStub,
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
):
    """
    RF Ping test that:
    - Ignore if the ping fails or ue can't attach
    - Fails only if ue/gnb/5gc crashes
    """

    with suppress(grpc.RpcError, AssertionError, Failed):
        _ping(
            retina_manager=retina_manager,
            retina_data=retina_data,
            ue_array=(ue_1, ue_2, ue_3, ue_4),
            gnb=gnb,
            fivegc=fivegc,
            band=band,
            common_scs=common_scs,
            bandwidth=bandwidth,
            sample_rate=None,  # default from testbed
            global_timing_advance=-1,
            time_alignment_calibration="auto",
            log_search=False,
            always_download_artifacts=True,
        )
    stop((ue_1, ue_2, ue_3, ue_4), gnb, fivegc, retina_data, log_search=False)


# pylint: disable=too-many-arguments, too-many-locals
def _ping(
    retina_manager: RetinaTestManager,
    retina_data: RetinaTestData,
    ue_array: Sequence[UEStub],
    fivegc: FiveGCStub,
    gnb: GNBStub,
    band: int,
    common_scs: int,
    bandwidth: int,
    sample_rate: Optional[int],
    global_timing_advance: int,
    time_alignment_calibration: Union[int, str],
    log_search: bool = True,
    warning_as_errors: bool = True,
    always_download_artifacts: bool = False,
    ping_count: int = 10,
    reattach_count: int = 0,
    pre_command: str = "",
    post_command: str = "",
    gnb_stop_timeout: int = 0,
    plmn: Optional[PLMN] = None,
):
    logging.info("Ping Test")

    configure_test_parameters(
        retina_manager=retina_manager,
        retina_data=retina_data,
        band=band,
        common_scs=common_scs,
        bandwidth=bandwidth,
        sample_rate=sample_rate,
        global_timing_advance=global_timing_advance,
        time_alignment_calibration=time_alignment_calibration,
        gtpu_enable=True,
    )
    configure_artifacts(
        retina_data=retina_data,
        always_download_artifacts=always_download_artifacts,
    )

    start_network(ue_array, gnb, fivegc, gnb_pre_cmd=pre_command, gnb_post_cmd=post_command, plmn=plmn)
    ue_attach_info_dict = ue_start_and_attach(ue_array, gnb, fivegc)
    ping(ue_attach_info_dict, fivegc, ping_count)

    # reattach and repeat if requested
    for _ in range(reattach_count):
        ue_stop(ue_array, retina_data)
        ue_attach_info_dict = ue_start_and_attach(ue_array, gnb, fivegc)
        ping(ue_attach_info_dict, fivegc, ping_count)

    # final stop
    stop(
        ue_array,
        gnb,
        fivegc,
        retina_data,
        gnb_stop_timeout=gnb_stop_timeout,
        log_search=log_search,
        warning_as_errors=warning_as_errors,
    )
