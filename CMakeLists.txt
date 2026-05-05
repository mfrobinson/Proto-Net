cmake_minimum_required(VERSION 3.10)
set(LIBRARY_NAME ProtoNet)
project(${LIBRARY_NAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)

# Set the declaration files
set(
	DECLARATIONS
	IP/TCP/Server/MultithreadedServer/Windows/IocpDataSocket.h
)
set(
	WINDOWS_DECLARATIONS
	IP/TCP/Server/Windows/MultithreadedServer.h
)
set(
	UNIX_DECLARATIONS
)
set(
	APPLE_DECLARATIONS
)

# Set the include files
set(
	INCLUDES
	IP/TCP/Server/MultithreadedServer/Callbacks/RecvCallback.h
	IP/TCP/Server/MultithreadedServer/Callbacks/RecvCallbackInvoker.h
	IP/TCP/Server/MultithreadedServer/Callbacks/SendCallback.h
	IP/TCP/Server/MultithreadedServer/Callbacks/SendCallbackInvoker.h
	IP/TCP/Server/MultithreadedServer/Info/BaseClientInfo.h
	IP/TCP/Server/MultithreadedServer/Info/BaseRecvInfo.h
	IP/TCP/Server/MultithreadedServer/Info/BaseSendInfo.h
	IP/TCP/Server/MultithreadedServer/Info/ClientInfo.h
	IP/TCP/Server/MultithreadedServer/Info/IoType.h
	IP/TCP/Server/MultithreadedServer/Info/OperationInfo.h
	IP/TCP/Server/MultithreadedServer/Info/RecvInfo.h
	IP/TCP/Server/MultithreadedServer/Info/SendInfo.h
	IP/TCP/Server/MultithreadedServer/Signatures/BaseRecvCallbackSignature.h
	IP/TCP/Server/MultithreadedServer/Signatures/BaseSendCallbackSignature.h
	IP/TCP/Server/MultithreadedServer/Signatures/RecvCallbackSignature.h
	IP/TCP/Server/MultithreadedServer/Signatures/SendCallbackSignature.h
	IP/TCP/DataSocket.h
	IP/TCP/Server.h
	IP/Endpoint.h
	IP/Socket.h
	Platform.h
)
set(
	WINDOWS_INCLUDES
	IP/TCP/Server/MultithreadedServer/Windows/create_new_recv_info.h
	IP/TCP/Server/MultithreadedServer/Windows/create_new_send_info.h
	IP/TCP/Server/MultithreadedServer/Windows/invoke_recv.h
	IP/TCP/Server/MultithreadedServer/Windows/invoke_recv_callback.h
	IP/TCP/Server/MultithreadedServer/Windows/invoke_send.h
	IP/TCP/Server/MultithreadedServer/Windows/invoke_send_callback.h
	IP/TCP/Server/MultithreadedServer/Windows/IocpDataSocket.h
	IP/TCP/Server/MultithreadedServer/Windows/OperationInfo.h
	IP/TCP/Server/Windows/MultithreadedServer.h
	IP/TCP/Windows/ClientSocket.h
	IP/TCP/Windows/DataSocket.h
	IP/TCP/Windows/ServerSocket.h
	IP/Windows/Endpoint.h
	IP/Windows/Socket.h
	IP/Windows/WinsockInstance.h
)
set(
	UNIX_INCLUDES
)
set(
	APPLE_INCLUDES
)

# Set the source files
set(
	WINDOWS_SOURCES
	IP/TCP/Windows/ClientSocket.cpp
	IP/TCP/Windows/DataSocket.cpp
	IP/TCP/Windows/ServerSocket.cpp
	Windows/Endpoint.cpp
	Windows/Socket.cpp
	Windows/WinsockInstance.cpp
)
list(TRANSFORM WINDOWS_SOURCES PREPEND "Src/Net/")

set(
	SOURCES
	IP/TCP/Server.cpp
)

# Append the appropriate platform includes and declarations to the generic includes and declarations
if (WIN32)
	list(APPEND INCLUDES ${WINDOWS_INCLUDES})
	list(APPEND DECLARATIONS ${WINDOWS_DECLARATIONS})
	list(APPEND SOURCES ${WINDOWS_SOURCES})
elseif(APPLE)
	list(APPEND INCLUDES ${APPLE_INCLUDES})
	list(APPEND DECLARATIONS ${APPLE_DECLARATIONS})
	list(APPEND SOURCES ${APPLE_SOURCES})
elseif (UNIX)
	list(APPEND INCLUDES ${UNIX_INCLUDES})
	list(APPEND DECLARATIONS ${UNIX_DECLARATIONS})
	list(APPEND SOURCES ${UNIX_SOURCES})
endif()

# Transform the includes and declarations to have the appropriate path
list(TRANSFORM INCLUDES PREPEND "Proto/Net/")
list(TRANSFORM DECLARATIONS PREPEND "Declarations/Proto/Net/")

# Merge the includes and declarations together since they are both to be includes
list(APPEND INCLUDES ${DECLARATIONS})

# Fetch dependencies
include(FetchContent)
FetchContent_Declare(
	ProtoComponents
	GIT_REPOSITORY https://github.com/mfrobinson/Proto-Components.git
	GIT_TAG master
)
FetchContent_MakeAvailable(ProtoComponents)


add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ProtoComponents)
target_sources (${PROJECT_NAME} PRIVATE ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
	$<INSTALL_INTERFACE:Include>
)
target_include_directories(${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:>
)