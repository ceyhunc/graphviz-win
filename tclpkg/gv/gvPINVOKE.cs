/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.26
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace gv {

using System;
using System.Runtime.InteropServices;

class gvPINVOKE {

  protected class SWIGExceptionHelper {

    public delegate void ExceptionDelegate(string message);
    public delegate void ExceptionArgumentDelegate(string message, string paramName);

    static ExceptionDelegate applicationDelegate = new ExceptionDelegate(SetPendingApplicationException);
    static ExceptionDelegate arithmeticDelegate = new ExceptionDelegate(SetPendingArithmeticException);
    static ExceptionDelegate divideByZeroDelegate = new ExceptionDelegate(SetPendingDivideByZeroException);
    static ExceptionDelegate indexOutOfRangeDelegate = new ExceptionDelegate(SetPendingIndexOutOfRangeException);
    static ExceptionDelegate invalidOperationDelegate = new ExceptionDelegate(SetPendingInvalidOperationException);
    static ExceptionDelegate ioDelegate = new ExceptionDelegate(SetPendingIOException);
    static ExceptionDelegate nullReferenceDelegate = new ExceptionDelegate(SetPendingNullReferenceException);
    static ExceptionDelegate outOfMemoryDelegate = new ExceptionDelegate(SetPendingOutOfMemoryException);
    static ExceptionDelegate overflowDelegate = new ExceptionDelegate(SetPendingOverflowException);
    static ExceptionDelegate systemDelegate = new ExceptionDelegate(SetPendingSystemException);

    static ExceptionArgumentDelegate argumentDelegate = new ExceptionArgumentDelegate(SetPendingArgumentException);
    static ExceptionArgumentDelegate argumentNullDelegate = new ExceptionArgumentDelegate(SetPendingArgumentNullException);
    static ExceptionArgumentDelegate argumentOutOfRangeDelegate = new ExceptionArgumentDelegate(SetPendingArgumentOutOfRangeException);

    [DllImport("gv", EntryPoint="SWIGRegisterExceptionCallbacks_gv")]
    public static extern void SWIGRegisterExceptionCallbacks_gv(
                                ExceptionDelegate applicationDelegate,
                                ExceptionDelegate arithmeticDelegate,
                                ExceptionDelegate divideByZeroDelegate, 
                                ExceptionDelegate indexOutOfRangeDelegate, 
                                ExceptionDelegate invalidOperationDelegate,
                                ExceptionDelegate ioDelegate,
                                ExceptionDelegate nullReferenceDelegate,
                                ExceptionDelegate outOfMemoryDelegate, 
                                ExceptionDelegate overflowDelegate, 
                                ExceptionDelegate systemExceptionDelegate);

    [DllImport("gv", EntryPoint="SWIGRegisterExceptionArgumentCallbacks_gv")]
    public static extern void SWIGRegisterExceptionCallbacksArgument_gv(
                                ExceptionArgumentDelegate argumentDelegate,
                                ExceptionArgumentDelegate argumentNullDelegate,
                                ExceptionArgumentDelegate argumentOutOfRangeDelegate);

    static void SetPendingApplicationException(string message) {
      SWIGPendingException.Set(new System.ApplicationException(message));
    }
    static void SetPendingArithmeticException(string message) {
      SWIGPendingException.Set(new System.ArithmeticException(message));
    }
    static void SetPendingDivideByZeroException(string message) {
      SWIGPendingException.Set(new System.DivideByZeroException(message));
    }
    static void SetPendingIndexOutOfRangeException(string message) {
      SWIGPendingException.Set(new System.IndexOutOfRangeException(message));
    }
    static void SetPendingInvalidOperationException(string message) {
      SWIGPendingException.Set(new System.InvalidOperationException(message));
    }
    static void SetPendingIOException(string message) {
      SWIGPendingException.Set(new System.IO.IOException(message));
    }
    static void SetPendingNullReferenceException(string message) {
      SWIGPendingException.Set(new System.NullReferenceException(message));
    }
    static void SetPendingOutOfMemoryException(string message) {
      SWIGPendingException.Set(new System.OutOfMemoryException(message));
    }
    static void SetPendingOverflowException(string message) {
      SWIGPendingException.Set(new System.OverflowException(message));
    }
    static void SetPendingSystemException(string message) {
      SWIGPendingException.Set(new System.SystemException(message));
    }

    static void SetPendingArgumentException(string message, string paramName) {
      SWIGPendingException.Set(new System.ArgumentException(message, paramName));
    }
    static void SetPendingArgumentNullException(string message, string paramName) {
      SWIGPendingException.Set(new System.ArgumentNullException(paramName, message));
    }
    static void SetPendingArgumentOutOfRangeException(string message, string paramName) {
      SWIGPendingException.Set(new System.ArgumentOutOfRangeException(paramName, message));
    }

    static SWIGExceptionHelper() {
      SWIGRegisterExceptionCallbacks_gv(
                                applicationDelegate,
                                arithmeticDelegate,
                                divideByZeroDelegate,
                                indexOutOfRangeDelegate,
                                invalidOperationDelegate,
                                ioDelegate,
                                nullReferenceDelegate,
                                outOfMemoryDelegate,
                                overflowDelegate,
                                systemDelegate);

      SWIGRegisterExceptionCallbacksArgument_gv(
                                argumentDelegate,
                                argumentNullDelegate,
                                argumentOutOfRangeDelegate);
    }
  }

  protected static SWIGExceptionHelper swigExceptionHelper = new SWIGExceptionHelper();

  public class SWIGPendingException {
    [ThreadStatic]
    private static Exception pendingException = null;
    private static int numExceptionsPending = 0;

    public static bool Pending {
      get {
        bool pending = false;
        if (numExceptionsPending > 0)
          if (pendingException != null)
            pending = true;
        return pending;
      } 
    }

    public static void Set(Exception e) {
      if (pendingException != null)
        throw new ApplicationException("FATAL: An earlier pending exception from unmanaged code was missed and thus not thrown (" + pendingException.ToString() + ")", e);
      pendingException = e;
      lock(typeof(gvPINVOKE)) {
        numExceptionsPending++;
      }
    }

    public static Exception Retrieve() {
      Exception e = null;
      if (numExceptionsPending > 0) {
        if (pendingException != null) {
          e = pendingException;
          pendingException = null;
          lock(typeof(gvPINVOKE)) {
            numExceptionsPending--;
          }
        }
      }
      return e;
    }
  }


  protected class SWIGStringHelper {

    public delegate string SWIGStringDelegate(string message);
    static SWIGStringDelegate stringDelegate = new SWIGStringDelegate(CreateString);

    [DllImport("gv", EntryPoint="SWIGRegisterStringCallback_gv")]
    public static extern void SWIGRegisterStringCallback_gv(SWIGStringDelegate stringDelegate);

    static string CreateString(string cString) {
      return cString;
    }

    static SWIGStringHelper() {
      SWIGRegisterStringCallback_gv(stringDelegate);
    }
  }

  static protected SWIGStringHelper swigStringHelper = new SWIGStringHelper();


  [DllImport("gv", EntryPoint="CSharp_graph__SWIG_0")]
  public static extern IntPtr graph__SWIG_0(string jarg1);

  [DllImport("gv", EntryPoint="CSharp_digraph")]
  public static extern IntPtr digraph(string jarg1);

  [DllImport("gv", EntryPoint="CSharp_strictgraph")]
  public static extern IntPtr strictgraph(string jarg1);

  [DllImport("gv", EntryPoint="CSharp_strictdigraph")]
  public static extern IntPtr strictdigraph(string jarg1);

  [DllImport("gv", EntryPoint="CSharp_readstring")]
  public static extern IntPtr readstring(string jarg1);

  [DllImport("gv", EntryPoint="CSharp_read__SWIG_0")]
  public static extern IntPtr read__SWIG_0(string jarg1);

  [DllImport("gv", EntryPoint="CSharp_read__SWIG_1")]
  public static extern IntPtr read__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_graph__SWIG_1")]
  public static extern IntPtr graph__SWIG_1(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_node")]
  public static extern IntPtr node(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_edge__SWIG_0")]
  public static extern IntPtr edge__SWIG_0(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_edge__SWIG_1")]
  public static extern IntPtr edge__SWIG_1(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_edge__SWIG_2")]
  public static extern IntPtr edge__SWIG_2(string jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_edge__SWIG_3")]
  public static extern IntPtr edge__SWIG_3(HandleRef jarg1, string jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_setv__SWIG_0")]
  public static extern string setv__SWIG_0(HandleRef jarg1, string jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_setv__SWIG_1")]
  public static extern string setv__SWIG_1(HandleRef jarg1, string jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_setv__SWIG_2")]
  public static extern string setv__SWIG_2(HandleRef jarg1, string jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_setv__SWIG_3")]
  public static extern string setv__SWIG_3(HandleRef jarg1, HandleRef jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_setv__SWIG_4")]
  public static extern string setv__SWIG_4(HandleRef jarg1, HandleRef jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_setv__SWIG_5")]
  public static extern string setv__SWIG_5(HandleRef jarg1, HandleRef jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_getv__SWIG_0")]
  public static extern string getv__SWIG_0(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_getv__SWIG_1")]
  public static extern string getv__SWIG_1(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_getv__SWIG_2")]
  public static extern string getv__SWIG_2(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_getv__SWIG_3")]
  public static extern string getv__SWIG_3(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_getv__SWIG_4")]
  public static extern string getv__SWIG_4(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_getv__SWIG_5")]
  public static extern string getv__SWIG_5(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_nameof__SWIG_0")]
  public static extern string nameof__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nameof__SWIG_1")]
  public static extern string nameof__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nameof__SWIG_2")]
  public static extern string nameof__SWIG_2(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_findsubg")]
  public static extern IntPtr findsubg(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_findnode")]
  public static extern IntPtr findnode(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_findedge")]
  public static extern IntPtr findedge(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_findattr__SWIG_0")]
  public static extern IntPtr findattr__SWIG_0(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_findattr__SWIG_1")]
  public static extern IntPtr findattr__SWIG_1(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_findattr__SWIG_2")]
  public static extern IntPtr findattr__SWIG_2(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_headof")]
  public static extern IntPtr headof(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_tailof")]
  public static extern IntPtr tailof(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_graphof__SWIG_0")]
  public static extern IntPtr graphof__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_graphof__SWIG_1")]
  public static extern IntPtr graphof__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_graphof__SWIG_2")]
  public static extern IntPtr graphof__SWIG_2(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_rootof")]
  public static extern IntPtr rootof(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_protonode")]
  public static extern IntPtr protonode(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_protoedge")]
  public static extern IntPtr protoedge(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_ok__SWIG_0")]
  public static extern bool ok__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_ok__SWIG_1")]
  public static extern bool ok__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_ok__SWIG_2")]
  public static extern bool ok__SWIG_2(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_ok__SWIG_3")]
  public static extern bool ok__SWIG_3(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_firstsubg")]
  public static extern IntPtr firstsubg(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextsubg")]
  public static extern IntPtr nextsubg(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstsupg")]
  public static extern IntPtr firstsupg(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextsupg")]
  public static extern IntPtr nextsupg(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstedge__SWIG_0")]
  public static extern IntPtr firstedge__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextedge__SWIG_0")]
  public static extern IntPtr nextedge__SWIG_0(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstout__SWIG_0")]
  public static extern IntPtr firstout__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextout__SWIG_0")]
  public static extern IntPtr nextout__SWIG_0(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstedge__SWIG_1")]
  public static extern IntPtr firstedge__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextedge__SWIG_1")]
  public static extern IntPtr nextedge__SWIG_1(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstout__SWIG_1")]
  public static extern IntPtr firstout__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextout__SWIG_1")]
  public static extern IntPtr nextout__SWIG_1(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firsthead")]
  public static extern IntPtr firsthead(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nexthead")]
  public static extern IntPtr nexthead(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstin__SWIG_0")]
  public static extern IntPtr firstin__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextin__SWIG_0")]
  public static extern IntPtr nextin__SWIG_0(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstin__SWIG_1")]
  public static extern IntPtr firstin__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextin__SWIG_1")]
  public static extern IntPtr nextin__SWIG_1(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firsttail")]
  public static extern IntPtr firsttail(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nexttail")]
  public static extern IntPtr nexttail(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstnode__SWIG_0")]
  public static extern IntPtr firstnode__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextnode__SWIG_0")]
  public static extern IntPtr nextnode__SWIG_0(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstnode__SWIG_1")]
  public static extern IntPtr firstnode__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextnode__SWIG_1")]
  public static extern IntPtr nextnode__SWIG_1(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstattr__SWIG_0")]
  public static extern IntPtr firstattr__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextattr__SWIG_0")]
  public static extern IntPtr nextattr__SWIG_0(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstattr__SWIG_1")]
  public static extern IntPtr firstattr__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextattr__SWIG_1")]
  public static extern IntPtr nextattr__SWIG_1(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_firstattr__SWIG_2")]
  public static extern IntPtr firstattr__SWIG_2(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_nextattr__SWIG_2")]
  public static extern IntPtr nextattr__SWIG_2(HandleRef jarg1, HandleRef jarg2);

  [DllImport("gv", EntryPoint="CSharp_rm__SWIG_0")]
  public static extern void rm__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_rm__SWIG_1")]
  public static extern void rm__SWIG_1(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_rm__SWIG_2")]
  public static extern void rm__SWIG_2(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_layout")]
  public static extern void layout(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_render__SWIG_0")]
  public static extern void render__SWIG_0(HandleRef jarg1);

  [DllImport("gv", EntryPoint="CSharp_render__SWIG_1")]
  public static extern void render__SWIG_1(HandleRef jarg1, string jarg2);

  [DllImport("gv", EntryPoint="CSharp_render__SWIG_2")]
  public static extern void render__SWIG_2(HandleRef jarg1, string jarg2, string jarg3);

  [DllImport("gv", EntryPoint="CSharp_render__SWIG_3")]
  public static extern void render__SWIG_3(HandleRef jarg1, string jarg2, HandleRef jarg3);

  [DllImport("gv", EntryPoint="CSharp_render__SWIG_4")]
  public static extern void render__SWIG_4(HandleRef jarg1, string jarg2, HandleRef jarg3);
}

}
