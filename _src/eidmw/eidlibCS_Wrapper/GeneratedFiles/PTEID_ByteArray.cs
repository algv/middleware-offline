/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.35
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace be.portugal.eid {

using System;
using System.Runtime.InteropServices;

public class PTEID_ByteArray : PTEID_Object {
  private HandleRef swigCPtr;

  internal PTEID_ByteArray(IntPtr cPtr, bool cMemoryOwn) : base(pteidlib_dotNetPINVOKE.PTEID_ByteArrayUpcast(cPtr), cMemoryOwn) {
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(PTEID_ByteArray obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~PTEID_ByteArray() {
    Dispose();
  }

  public override void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        pteidlib_dotNetPINVOKE.delete_PTEID_ByteArray(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
      base.Dispose();
    }
  }

  public PTEID_ByteArray() : this(pteidlib_dotNetPINVOKE.new_PTEID_ByteArray__SWIG_0(), true) {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public PTEID_ByteArray(PTEID_ByteArray bytearray) : this(pteidlib_dotNetPINVOKE.new_PTEID_ByteArray__SWIG_1(PTEID_ByteArray.getCPtr(bytearray)), true) {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public PTEID_ByteArray(byte[] pucData, uint ulSize) : this(pteidlib_dotNetPINVOKE.new_PTEID_ByteArray__SWIG_2(pucData, ulSize), true) {
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Append(byte[] pucData, uint ulSize) {
    pteidlib_dotNetPINVOKE.PTEID_ByteArray_Append__SWIG_0(swigCPtr, pucData, ulSize);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Append(PTEID_ByteArray data) {
    pteidlib_dotNetPINVOKE.PTEID_ByteArray_Append__SWIG_1(swigCPtr, PTEID_ByteArray.getCPtr(data));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public void Clear() {
    pteidlib_dotNetPINVOKE.PTEID_ByteArray_Clear(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
  }

  public bool Equals(PTEID_ByteArray data) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_ByteArray_Equals(swigCPtr, PTEID_ByteArray.getCPtr(data));
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public uint Size() {
    uint ret = pteidlib_dotNetPINVOKE.PTEID_ByteArray_Size(swigCPtr);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public byte[] GetBytes() { 
	byte[] rslt = new byte[Size()];
	IntPtr pt = pteidlib_dotNetPINVOKE.PTEID_ByteArray_GetBytes(swigCPtr);
	if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
	Marshal.Copy(pt, rslt, 0,(int) Size());
	return rslt; 
}

  public bool writeToFile(string csFilePath) {
    bool ret = pteidlib_dotNetPINVOKE.PTEID_ByteArray_writeToFile(swigCPtr, csFilePath);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

  public PTEID_ByteArray assign(PTEID_ByteArray bytearray) {
    PTEID_ByteArray ret = new PTEID_ByteArray(pteidlib_dotNetPINVOKE.PTEID_ByteArray_assign(swigCPtr, PTEID_ByteArray.getCPtr(bytearray)), false);
    if (pteidlib_dotNetPINVOKE.SWIGPendingException.Pending) throw pteidlib_dotNetPINVOKE.SWIGPendingException.Retrieve();
    return ret;
  }

}

}
