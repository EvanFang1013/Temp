using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Modbus;
using Modbus.Device;
using Modbus.Data;
using Modbus.Message;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace tcp_slave
{
    public class modbusLib
    {
        TcpListener slaveTcpListener;
        Modbus.Device.ModbusSlave slave;

        private byte _slaveID;
        private int _port = 502;
        private string _ip;

        private byte SlaveID { set { this._slaveID = value; } }
        private string Hostip { set { this._ip = value; } }
        private void Modbus_Request_Event(object sender, Modbus.Device.ModbusSlaveRequestEventArgs e)
        {
            //request from master//disassemble packet from master
            byte fc = e.Message.FunctionCode;
            byte[] data = e.Message.MessageFrame;
            byte[] byteStartAddress = new byte[] { data[3], data[2] };
            byte[] byteNum = new byte[] { data[5], data[4] };
            Int16 StartAddress = BitConverter.ToInt16(byteStartAddress, 0);
            Int16 NumOfPoint = BitConverter.ToInt16(byteNum, 0);
        }

        /// <summary>
        /// Initial slave ID & host IP
        /// </summary>
        /// <param name="slaveID"></param>
        /// <param name="HostIp"></param>
        public modbusLib(string HostIp, byte slaveID)
        {
            SlaveID = slaveID;
            Hostip = HostIp;
        }

        /// <summary>
        /// Start listen Modbus server
        /// </summary>
        public void TCPStart()
        {
            IPAddress ipstate;
            ipstate = IPAddress.Parse(_ip);
            slaveTcpListener = new TcpListener(ipstate, _port);
            slaveTcpListener.Start();
            slave = Modbus.Device.ModbusTcpSlave.CreateTcp(_slaveID, slaveTcpListener);
            slave.ModbusSlaveRequestReceived += new EventHandler<ModbusSlaveRequestEventArgs>(Modbus_Request_Event);
            slave.Listen();
        }
        /// <summary>
        /// Stop listen Modbus server
        /// </summary>
        public void TCPstop()
        {
            slaveTcpListener.Stop();
            slaveTcpListener = null;
            slave.Stop();
            slave.Dispose();
        }

        /// <summary>
        /// Send data 
        /// When data is Double condition
        /// </summary>
        /// <param name="data"></param>
        public void Sendata(double[] data)
        {
            for (int i = 0; i < data.Length; i++)
            {
                slave.DataStore.HoldingRegisters[i + 1] = Convert.ToUInt16(data[i]);
            }

        }
        /// <summary>
        /// Send data 
        /// When data is int condition
        /// </summary>
        /// <param name="data"></param>
        public void Sendata(int[] data)
        {
            for (int i = 0; i < data.Length; i++)
            {
                slave.DataStore.HoldingRegisters[i + 1] = Convert.ToUInt16(data[i]);
            }

        }

        /// <summary>
        /// Send data 
        /// When data is list<double> condition
        /// </summary>
        /// <param name="data"></param>
        public void Sendata(List<double> data)
        {
            for (int i = 0; i < data.Count; i++)
            {
                slave.DataStore.HoldingRegisters[i + 1] = Convert.ToUInt16(data[i]);
            }

        }

        /// <summary>
        /// Send data 
        /// When data is list<int> condition
        /// </summary>
        /// <param name="data"></param>
        public void Sendata(List<int> data)
        {
            for (int i = 0; i < data.Count; i++)
            {
                slave.DataStore.HoldingRegisters[i + 1] = Convert.ToUInt16(data[i]);
            }

        }


    }
}
