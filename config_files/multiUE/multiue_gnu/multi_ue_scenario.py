#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: srsRAN_multi_UE
# GNU Radio version: 3.10.1.1

from packaging.version import Version as StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from gnuradio import blocks
from gnuradio import gr
from gnuradio.filter import firdes
from gnuradio.fft import window
import sys
import signal
from PyQt5 import Qt
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio import zeromq
from gnuradio.qtgui import Range, RangeWidget
from PyQt5 import QtCore



from gnuradio import qtgui

class multi_ue_scenario(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "srsRAN_multi_UE", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("srsRAN_multi_UE")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "multi_ue_scenario")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.zmq_timeout = zmq_timeout = 100
        self.zmq_hwm = zmq_hwm = -1
        self.ue3_path_loss_db = ue3_path_loss_db = 20
        self.ue2_path_loss_db = ue2_path_loss_db = 10
        self.ue1_path_loss_db = ue1_path_loss_db = 0
        self.slow_down_ratio = slow_down_ratio = 4
        self.samp_rate = samp_rate = 11520000

        ##################################################
        # Blocks
        ##################################################
        self._ue3_path_loss_db_range = Range(0, 100, 1, 20, 200)
        self._ue3_path_loss_db_win = RangeWidget(self._ue3_path_loss_db_range, self.set_ue3_path_loss_db, "UE3 Pathloss [dB]", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._ue3_path_loss_db_win)
        self._ue2_path_loss_db_range = Range(0, 100, 1, 10, 200)
        self._ue2_path_loss_db_win = RangeWidget(self._ue2_path_loss_db_range, self.set_ue2_path_loss_db, "UE2 Pathloss [dB]", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._ue2_path_loss_db_win)
        self._ue1_path_loss_db_range = Range(0, 100, 1, 0, 200)
        self._ue1_path_loss_db_win = RangeWidget(self._ue1_path_loss_db_range, self.set_ue1_path_loss_db, "UE1 Pathloss [dB]", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._ue1_path_loss_db_win)
        self._slow_down_ratio_range = Range(1, 32, 1, 4, 200)
        self._slow_down_ratio_win = RangeWidget(self._slow_down_ratio_range, self.set_slow_down_ratio, "Time Slow Down Ratio", "counter_slider", float, QtCore.Qt.Horizontal)
        self.top_layout.addWidget(self._slow_down_ratio_win)
        self.zeromq_req_source_1_0 = zeromq.req_source(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2201', zmq_timeout, False, zmq_hwm)
        self.zeromq_req_source_1 = zeromq.req_source(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2101', zmq_timeout, False, zmq_hwm)
        self.zeromq_req_source_0_0 = zeromq.req_source(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2301', zmq_timeout, False, zmq_hwm)
        self.zeromq_req_source_0 = zeromq.req_source(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2000', zmq_timeout, False, zmq_hwm)
        self.zeromq_rep_sink_0_2 = zeromq.rep_sink(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2300', 100, False, zmq_hwm)
        self.zeromq_rep_sink_0_1 = zeromq.rep_sink(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2001', zmq_timeout, False, zmq_hwm)
        self.zeromq_rep_sink_0_0 = zeromq.rep_sink(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2200', zmq_timeout, False, zmq_hwm)
        self.zeromq_rep_sink_0 = zeromq.rep_sink(gr.sizeof_gr_complex, 1, 'tcp://127.0.0.1:2100', zmq_timeout, False, zmq_hwm)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, 1.0*samp_rate/(1.0*slow_down_ratio),True)
        self.blocks_multiply_const_vxx_0_1_1 = blocks.multiply_const_cc(10**(-1.0*ue2_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_1_0 = blocks.multiply_const_cc(10**(-1.0*ue3_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_1 = blocks.multiply_const_cc(10**(-1.0*ue1_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_0_0 = blocks.multiply_const_cc(10**(-1.0*ue3_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_0 = blocks.multiply_const_cc(10**(-1.0*ue2_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_cc(10**(-1.0*ue1_path_loss_db/20.0))
        self.blocks_add_xx_0 = blocks.add_vcc(1)


        ##################################################
        # Connections
        ##################################################
        self.connect((self.blocks_add_xx_0, 0), (self.zeromq_rep_sink_0_1, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_multiply_const_vxx_0_0_0, 0), (self.blocks_add_xx_0, 2))
        self.connect((self.blocks_multiply_const_vxx_0_1, 0), (self.zeromq_rep_sink_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0_1_0, 0), (self.zeromq_rep_sink_0_2, 0))
        self.connect((self.blocks_multiply_const_vxx_0_1_1, 0), (self.zeromq_rep_sink_0_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_multiply_const_vxx_0_1, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_multiply_const_vxx_0_1_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.blocks_multiply_const_vxx_0_1_1, 0))
        self.connect((self.zeromq_req_source_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.zeromq_req_source_0_0, 0), (self.blocks_multiply_const_vxx_0_0_0, 0))
        self.connect((self.zeromq_req_source_1, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.zeromq_req_source_1_0, 0), (self.blocks_multiply_const_vxx_0_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "multi_ue_scenario")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_zmq_timeout(self):
        return self.zmq_timeout

    def set_zmq_timeout(self, zmq_timeout):
        self.zmq_timeout = zmq_timeout

    def get_zmq_hwm(self):
        return self.zmq_hwm

    def set_zmq_hwm(self, zmq_hwm):
        self.zmq_hwm = zmq_hwm

    def get_ue3_path_loss_db(self):
        return self.ue3_path_loss_db

    def set_ue3_path_loss_db(self, ue3_path_loss_db):
        self.ue3_path_loss_db = ue3_path_loss_db
        self.blocks_multiply_const_vxx_0_0_0.set_k(10**(-1.0*self.ue3_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_1_0.set_k(10**(-1.0*self.ue3_path_loss_db/20.0))

    def get_ue2_path_loss_db(self):
        return self.ue2_path_loss_db

    def set_ue2_path_loss_db(self, ue2_path_loss_db):
        self.ue2_path_loss_db = ue2_path_loss_db
        self.blocks_multiply_const_vxx_0_0.set_k(10**(-1.0*self.ue2_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_1_1.set_k(10**(-1.0*self.ue2_path_loss_db/20.0))

    def get_ue1_path_loss_db(self):
        return self.ue1_path_loss_db

    def set_ue1_path_loss_db(self, ue1_path_loss_db):
        self.ue1_path_loss_db = ue1_path_loss_db
        self.blocks_multiply_const_vxx_0.set_k(10**(-1.0*self.ue1_path_loss_db/20.0))
        self.blocks_multiply_const_vxx_0_1.set_k(10**(-1.0*self.ue1_path_loss_db/20.0))

    def get_slow_down_ratio(self):
        return self.slow_down_ratio

    def set_slow_down_ratio(self, slow_down_ratio):
        self.slow_down_ratio = slow_down_ratio
        self.blocks_throttle_0.set_sample_rate(1.0*self.samp_rate/(1.0*self.slow_down_ratio))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.blocks_throttle_0.set_sample_rate(1.0*self.samp_rate/(1.0*self.slow_down_ratio))




def main(top_block_cls=multi_ue_scenario, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
