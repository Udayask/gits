// ===================== begin_copyright_notice ============================
//
// Copyright (C) 2023-2025 Intel Corporation
//
// SPDX-License-Identifier: MIT
//
// ===================== end_copyright_notice ==============================

#include "captureCustomizationLayer.h"
#include "captureManager.h"
#include "commandsCustom.h"
#include "commandWritersCustom.h"
#include "commandWritersAuto.h"
#include "iunknownWrapper.h"
#include "wrapperUtils.h"
#include "objectInfos.h"
#include "gits.h"

#include <windows.h>

namespace gits {
namespace DirectX {

CaptureCustomizationLayer::CaptureCustomizationLayer(CaptureManager& manager,
                                                     GitsRecorder& recorder)
    : Layer("CaptureCustomization"), manager_(manager), recorder_(recorder) {}

void CaptureCustomizationLayer::post(IUnknownReleaseCommand& c) {
  if (c.result_.value == 0) {
    manager_.getDescriptorHandleService().destroyDescriptorHeap(c.object_.key);
    manager_.getMapTrackingService().destroyResource(c.object_.key);
    manager_.getGpuAddressService().destroyInterface(c.object_.key);
    manager_.getFenceService().destroyFence(c.object_.key);
  }
}

void CaptureCustomizationLayer::pre(IDXGIFactoryCreateSwapChainCommand& c) {
  RECT rect;
  BOOL ret = GetClientRect(c.pDesc_.value->OutputWindow, &rect);
  GITS_ASSERT(ret);

  CreateWindowMetaCommand createWindowCommand(c.threadId);
  createWindowCommand.key = manager_.createCommandKey();
  createWindowCommand.hWnd_.value = c.pDesc_.value->OutputWindow;
  createWindowCommand.width_.value = rect.right - rect.left;
  createWindowCommand.height_.value = rect.bottom - rect.top;
  createWindowCommand.width_.value = std::max(
      static_cast<unsigned>(createWindowCommand.width_.value), c.pDesc_.value->BufferDesc.Width);
  createWindowCommand.height_.value = std::max(
      static_cast<unsigned>(createWindowCommand.height_.value), c.pDesc_.value->BufferDesc.Height);

  recorder_.record(createWindowCommand.key, new CreateWindowMetaWriter(createWindowCommand));
}

void CaptureCustomizationLayer::pre(IDXGIFactory2CreateSwapChainForHwndCommand& c) {
  RECT rect;
  BOOL ret = GetClientRect(c.hWnd_.value, &rect);
  GITS_ASSERT(ret);

  CreateWindowMetaCommand createWindowCommand(c.threadId);
  createWindowCommand.key = manager_.createCommandKey();
  createWindowCommand.hWnd_ = c.hWnd_;
  createWindowCommand.width_.value = rect.right - rect.left;
  createWindowCommand.height_.value = rect.bottom - rect.top;
  createWindowCommand.width_.value =
      std::max(static_cast<unsigned>(createWindowCommand.width_.value), c.pDesc_.value->Width);
  createWindowCommand.height_.value =
      std::max(static_cast<unsigned>(createWindowCommand.height_.value), c.pDesc_.value->Height);

  recorder_.record(createWindowCommand.key, new CreateWindowMetaWriter(createWindowCommand));
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreateDescriptorHeapCommand& c) {
  if (c.result_.value != S_OK) {
    return;
  }
  ID3D12DescriptorHeap* descriptorHeap = static_cast<ID3D12DescriptorHeap*>(*c.ppvHeap_.value);
  manager_.getDescriptorHandleService().createDescriptorHeap(c.ppvHeap_.key, descriptorHeap,
                                                             c.pDescriptorHeapDesc_.value);
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateCommittedResourceCommand& c) {
  c.pHeapProperties_.originalValue = *c.pHeapProperties_.value;
  c.HeapFlags_.originalValue = c.HeapFlags_.value;
  manager_.getMapTrackingService().enableWriteWatch(*c.pHeapProperties_.value, c.HeapFlags_.value);
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreateCommittedResourceCommand& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
    *c.pHeapProperties_.value = c.pHeapProperties_.originalValue;
    c.HeapFlags_.value = c.HeapFlags_.originalValue;
  }
}

void CaptureCustomizationLayer::pre(ID3D12Device4CreateCommittedResource1Command& c) {
  c.pHeapProperties_.originalValue = *c.pHeapProperties_.value;
  c.HeapFlags_.originalValue = c.HeapFlags_.value;
  manager_.getMapTrackingService().enableWriteWatch(*c.pHeapProperties_.value, c.HeapFlags_.value);
}

void CaptureCustomizationLayer::post(ID3D12Device4CreateCommittedResource1Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
    *c.pHeapProperties_.value = c.pHeapProperties_.originalValue;
    c.HeapFlags_.value = c.HeapFlags_.originalValue;
  }
}

void CaptureCustomizationLayer::pre(ID3D12Device8CreateCommittedResource2Command& c) {
  c.pHeapProperties_.originalValue = *c.pHeapProperties_.value;
  c.HeapFlags_.originalValue = c.HeapFlags_.value;
  manager_.getMapTrackingService().enableWriteWatch(*c.pHeapProperties_.value, c.HeapFlags_.value);
}

void CaptureCustomizationLayer::post(ID3D12Device8CreateCommittedResource2Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
    *c.pHeapProperties_.value = c.pHeapProperties_.originalValue;
    c.HeapFlags_.value = c.HeapFlags_.originalValue;
  }
}

void CaptureCustomizationLayer::pre(ID3D12Device10CreateCommittedResource3Command& c) {
  c.pHeapProperties_.originalValue = *c.pHeapProperties_.value;
  c.HeapFlags_.originalValue = c.HeapFlags_.value;
  manager_.getMapTrackingService().enableWriteWatch(*c.pHeapProperties_.value, c.HeapFlags_.value);
}

void CaptureCustomizationLayer::post(ID3D12Device10CreateCommittedResource3Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
    *c.pHeapProperties_.value = c.pHeapProperties_.originalValue;
    c.HeapFlags_.value = c.HeapFlags_.originalValue;
  }
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreateReservedResourceCommand& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
  }
}

void CaptureCustomizationLayer::post(ID3D12Device4CreateReservedResource1Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
  }
}

void CaptureCustomizationLayer::post(ID3D12Device10CreateReservedResource2Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createResource(c.ppvResource_.key, resource);
  }
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreatePlacedResourceCommand& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createPlacedResource(c.ppvResource_.key, resource, c.pHeap_.key,
                                                         c.pHeap_.value, c.HeapOffset_.value);
  }
}

void CaptureCustomizationLayer::post(ID3D12Device8CreatePlacedResource1Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createPlacedResource(c.ppvResource_.key, resource, c.pHeap_.key,
                                                         c.pHeap_.value, c.HeapOffset_.value);
  }
}

void CaptureCustomizationLayer::post(ID3D12Device10CreatePlacedResource2Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvResource_.value);
    manager_.getGpuAddressService().createPlacedResource(c.ppvResource_.key, resource, c.pHeap_.key,
                                                         c.pHeap_.value, c.HeapOffset_.value);
  }
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateHeapCommand& c) {
  c.pDesc_.originalValue = *c.pDesc_.value;
  manager_.getMapTrackingService().enableWriteWatch(c.pDesc_.value->Properties,
                                                    c.pDesc_.value->Flags);
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreateHeapCommand& c) {
  if (c.result_.value == S_OK) {
    ID3D12Heap* heap = static_cast<ID3D12Heap*>(*c.ppvHeap_.value);
    manager_.getGpuAddressService().createHeap(c.ppvHeap_.key, heap);
    *c.pDesc_.value = c.pDesc_.originalValue;
  }
}

void CaptureCustomizationLayer::pre(ID3D12Device4CreateHeap1Command& c) {
  c.pDesc_.originalValue = *c.pDesc_.value;
  manager_.getMapTrackingService().enableWriteWatch(c.pDesc_.value->Properties,
                                                    c.pDesc_.value->Flags);
}

void CaptureCustomizationLayer::post(ID3D12Device4CreateHeap1Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Heap* heap = static_cast<ID3D12Heap*>(*c.ppvHeap_.value);
    manager_.getGpuAddressService().createHeap(c.ppvHeap_.key, heap);
    *c.pDesc_.value = c.pDesc_.originalValue;
  }
}

void CaptureCustomizationLayer::post(ID3D12Device3OpenExistingHeapFromAddressCommand& c) {
  if (c.result_.value == S_OK) {
    ID3D12Heap* heap = static_cast<ID3D12Heap*>(*c.ppvHeap_.value);
    manager_.getGpuAddressService().createHeap(c.ppvHeap_.key, heap);

    D3D12_HEAP_DESC desc = heap->GetDesc();

    CreateHeapAllocationMetaCommand command(c.threadId);
    command.key = manager_.createCommandKey();
    command.heap_.key = c.ppvHeap_.key;
    command.address_.value = const_cast<void*>(c.pAddress_.value);
    command.data_.value = const_cast<void*>(c.pAddress_.value);
    command.data_.size = desc.SizeInBytes;
    recorder_.record(command.key, new CreateHeapAllocationMetaWriter(command));

    manager_.updateCommandKey(c);
  }
}

void CaptureCustomizationLayer::post(ID3D12Device13OpenExistingHeapFromAddress1Command& c) {
  if (c.result_.value == S_OK) {
    ID3D12Heap* heap = static_cast<ID3D12Heap*>(*c.ppvHeap_.value);
    manager_.getGpuAddressService().createHeap(c.ppvHeap_.key, heap);

    D3D12_HEAP_DESC desc = heap->GetDesc();

    CreateHeapAllocationMetaCommand command(c.threadId);
    command.key = manager_.createCommandKey();
    command.heap_.key = c.ppvHeap_.key;
    command.address_.value = const_cast<void*>(c.pAddress_.value);
    command.data_.value = const_cast<void*>(c.pAddress_.value);
    command.data_.size = desc.SizeInBytes;
    recorder_.record(command.key, new CreateHeapAllocationMetaWriter(command));

    manager_.updateCommandKey(c);
  }
}

void CaptureCustomizationLayer::post(ID3D12ResourceMapCommand& c) {
  if (c.result_.value != S_OK) {
    return;
  }
  manager_.getMapTrackingService().mapResource(c.object_.key, c.object_.value, c.Subresource_.value,
                                               c.ppData_.value);
}

void CaptureCustomizationLayer::pre(ID3D12ResourceUnmapCommand& c) {
  manager_.getMapTrackingService().unmapResource(c.object_.key, c.Subresource_.value);
}

void CaptureCustomizationLayer::pre(ID3D12CommandQueueExecuteCommandListsCommand& c) {
  manager_.getMapTrackingService().executeCommandLists();
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateRenderTargetViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateShaderResourceViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  if (c.pDesc_.value &&
      c.pDesc_.value->ViewDimension == D3D12_SRV_DIMENSION_RAYTRACING_ACCELERATION_STRUCTURE) {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->RaytracingAccelerationStructure.Location);
    c.pDesc_.raytracingLocationKey = info.resourceKey;
    c.pDesc_.raytracingLocationOffset = info.offset;
  }
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateUnorderedAccessViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateDepthStencilViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

void CaptureCustomizationLayer::pre(
    ID3D12Device8CreateSamplerFeedbackUnorderedAccessViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateSamplerCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
}

void CaptureCustomizationLayer::pre(ID3D12Device11CreateSampler2Command& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetGraphicsRootDescriptorTableCommand& c) {

  std::lock_guard<std::mutex> lock(*c.object_.objectInfo->getMutex());
  CommandListObjectInfo* info = c.object_.objectInfo->getObjectInfo<CommandListObjectInfo>(this);
  D3D12_DESCRIPTOR_HEAP_TYPE heapType =
      info->graphicsRootSignatureInfo->getDescriptorTableHeapType(c.RootParameterIndex_.value);
  fillGpuDescriptorHandleArgument(c.BaseDescriptor_, heapType);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetComputeRootDescriptorTableCommand& c) {

  std::lock_guard<std::mutex> lock(*c.object_.objectInfo->getMutex());
  CommandListObjectInfo* info = c.object_.objectInfo->getObjectInfo<CommandListObjectInfo>(this);
  D3D12_DESCRIPTOR_HEAP_TYPE heapType =
      info->computeRootSignatureInfo->getDescriptorTableHeapType(c.RootParameterIndex_.value);
  fillGpuDescriptorHandleArgument(c.BaseDescriptor_, heapType);
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandListOMSetRenderTargetsCommand& c) {

  if (c.pRenderTargetDescriptors_.value) {
    for (unsigned i = 0; i < c.NumRenderTargetDescriptors_.value; ++i) {
      CaptureDescriptorHandleService::HandleInfo info =
          manager_.getDescriptorHandleService().getDescriptorHandleInfo(
              D3D12_DESCRIPTOR_HEAP_TYPE_RTV, CaptureDescriptorHandleService::HandleType::CpuHandle,
              c.pRenderTargetDescriptors_.value[i].ptr);
      c.pRenderTargetDescriptors_.interfaceKeys[i] = info.interfaceKey;
      c.pRenderTargetDescriptors_.indexes[i] = info.index;
    }
  }
  if (c.pDepthStencilDescriptor_.value) {
    CaptureDescriptorHandleService::HandleInfo info =
        manager_.getDescriptorHandleService().getDescriptorHandleInfo(
            D3D12_DESCRIPTOR_HEAP_TYPE_DSV, CaptureDescriptorHandleService::HandleType::CpuHandle,
            c.pDepthStencilDescriptor_.value[0].ptr);
    c.pDepthStencilDescriptor_.interfaceKeys[0] = info.interfaceKey;
    c.pDepthStencilDescriptor_.indexes[0] = info.index;
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandListClearDepthStencilViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DepthStencilView_, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandListClearRenderTargetViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.RenderTargetView_, D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListClearUnorderedAccessViewUintCommand& c) {
  fillGpuDescriptorHandleArgument(c.ViewGPUHandleInCurrentHeap_,
                                  D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  fillCpuDescriptorHandleArgument(c.ViewCPUHandle_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListClearUnorderedAccessViewFloatCommand& c) {
  fillGpuDescriptorHandleArgument(c.ViewGPUHandleInCurrentHeap_,
                                  D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  fillCpuDescriptorHandleArgument(c.ViewCPUHandle_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCopyDescriptorsCommand& c) {

  for (unsigned i = 0; i < c.NumDestDescriptorRanges_.value; ++i) {
    CaptureDescriptorHandleService::HandleInfo info =
        manager_.getDescriptorHandleService().getDescriptorHandleInfo(
            c.DescriptorHeapsType_.value, CaptureDescriptorHandleService::HandleType::CpuHandle,
            c.pDestDescriptorRangeStarts_.value[i].ptr);

    c.pDestDescriptorRangeStarts_.interfaceKeys[i] = info.interfaceKey;
    c.pDestDescriptorRangeStarts_.indexes[i] = info.index;
  }
  for (unsigned i = 0; i < c.NumSrcDescriptorRanges_.value; ++i) {
    CaptureDescriptorHandleService::HandleInfo info =
        manager_.getDescriptorHandleService().getDescriptorHandleInfo(
            c.DescriptorHeapsType_.value, CaptureDescriptorHandleService::HandleType::CpuHandle,
            c.pSrcDescriptorRangeStarts_.value[i].ptr);

    c.pSrcDescriptorRangeStarts_.interfaceKeys[i] = info.interfaceKey;
    c.pSrcDescriptorRangeStarts_.indexes[i] = info.index;
  }
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCopyDescriptorsSimpleCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptorRangeStart_, c.DescriptorHeapsType_.value);
  fillCpuDescriptorHandleArgument(c.SrcDescriptorRangeStart_, c.DescriptorHeapsType_.value);
}

void CaptureCustomizationLayer::post(D3D12SerializeRootSignatureCommand& c) {
  manager_.getRootSignatureService().serializeRootSignature(c.pRootSignature_.value, c.ppBlob_.key);
}

void CaptureCustomizationLayer::post(D3D12SerializeVersionedRootSignatureCommand& c) {
  manager_.getRootSignatureService().serializeVersionedRootSignature(c.pRootSignature_.value,
                                                                     c.ppBlob_.key);
}

void CaptureCustomizationLayer::post(ID3DBlobGetBufferPointerCommand& c) {
  manager_.getRootSignatureService().setBlobBufferPointer(c.object_.key, c.result_.value);
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreateRootSignatureCommand& c) {
  if (c.result_.value == S_OK) {
    manager_.getRootSignatureService().createRootSignature(c.pBlobWithRootSignature_.value,
                                                           c.blobLengthInBytes_.value,
                                                           c.ppvRootSignature_.objectInfo, this);
  }
}

void CaptureCustomizationLayer::post(ID3D12DeviceCreateCommandListCommand& c) {
  c.ppCommandList_.objectInfo->addObjectInfo(this, new CommandListObjectInfo());
}

void CaptureCustomizationLayer::post(ID3D12Device4CreateCommandList1Command& c) {
  c.ppCommandList_.objectInfo->addObjectInfo(this, new CommandListObjectInfo());
}

void CaptureCustomizationLayer::post(ID3D12GraphicsCommandListSetGraphicsRootSignatureCommand& c) {
  // pRootSignature is optional, so it can be nullptr
  if (!c.pRootSignature_.value) {
    return;
  }

  std::lock_guard<std::mutex> lock(*c.object_.objectInfo->getMutex());
  CommandListObjectInfo* info = c.object_.objectInfo->getObjectInfo<CommandListObjectInfo>(this);
  info->graphicsRootSignatureInfo =
      c.pRootSignature_.objectInfo->getObjectInfo<RootSignatureObjectInfo>(this);
}

void CaptureCustomizationLayer::post(ID3D12GraphicsCommandListSetComputeRootSignatureCommand& c) {
  // pRootSignature is optional, so it can be nullptr
  if (!c.pRootSignature_.value) {
    return;
  }

  std::lock_guard<std::mutex> lock(*c.object_.objectInfo->getMutex());
  CommandListObjectInfo* info = c.object_.objectInfo->getObjectInfo<CommandListObjectInfo>(this);
  info->computeRootSignatureInfo =
      c.pRootSignature_.objectInfo->getObjectInfo<RootSignatureObjectInfo>(this);
}

void CaptureCustomizationLayer::post(ID3D12GraphicsCommandListResetCommand& c) {

  std::lock_guard<std::mutex> lock(*c.object_.objectInfo->getMutex());
  CommandListObjectInfo* info = c.object_.objectInfo->getObjectInfo<CommandListObjectInfo>(this);
  info->graphicsRootSignatureInfo = nullptr;
  info->computeRootSignatureInfo = nullptr;
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetComputeRootConstantBufferViewCommand& c) {
  fillGpuAddressArgument(c.BufferLocation_);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetGraphicsRootConstantBufferViewCommand& c) {
  fillGpuAddressArgument(c.BufferLocation_);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetComputeRootShaderResourceViewCommand& c) {
  fillGpuAddressArgument(c.BufferLocation_);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetGraphicsRootShaderResourceViewCommand& c) {
  fillGpuAddressArgument(c.BufferLocation_);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetComputeRootUnorderedAccessViewCommand& c) {
  fillGpuAddressArgument(c.BufferLocation_);
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandListSetGraphicsRootUnorderedAccessViewCommand& c) {
  fillGpuAddressArgument(c.BufferLocation_);
}

void CaptureCustomizationLayer::pre(ID3D12DeviceCreateConstantBufferViewCommand& c) {
  fillCpuDescriptorHandleArgument(c.DestDescriptor_, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  if (c.pDesc_.value && c.pDesc_.value->BufferLocation) {
    GpuAddressService::GpuAddressInfo info =
        manager_.getGpuAddressService().getGpuAddressInfo(c.pDesc_.value->BufferLocation);
    c.pDesc_.bufferLocationKey = info.resourceKey;
    c.pDesc_.bufferLocationOffset = info.offset;
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandListIASetIndexBufferCommand& c) {
  if (c.pView_.value && c.pView_.value->BufferLocation) {
    GpuAddressService::GpuAddressInfo info =
        manager_.getGpuAddressService().getGpuAddressInfo(c.pView_.value->BufferLocation);
    c.pView_.bufferLocationKey = info.resourceKey;
    c.pView_.bufferLocationOffset = info.offset;
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandListIASetVertexBuffersCommand& c) {
  if (c.pViews_.value) {
    for (unsigned i = 0; i < c.NumViews_.value; ++i) {
      if (c.pViews_.value[i].BufferLocation) {
        GpuAddressService::GpuAddressInfo info =
            manager_.getGpuAddressService().getGpuAddressInfo(c.pViews_.value[i].BufferLocation);
        c.pViews_.bufferLocationKeys[i] = info.resourceKey;
        c.pViews_.bufferLocationOffsets[i] = info.offset;
      }
    }
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandListSOSetTargetsCommand& c) {
  if (c.pViews_.value) {
    for (unsigned i = 0; i < c.NumViews_.value; ++i) {
      if (c.pViews_.value[i].BufferLocation) {
        GpuAddressService::GpuAddressInfo info =
            manager_.getGpuAddressService().getGpuAddressInfo(c.pViews_.value[i].BufferLocation);
        c.pViews_.bufferLocationKeys[i] = info.resourceKey;
        c.pViews_.bufferLocationOffsets[i] = info.offset;
      }
      if (c.pViews_.value[i].BufferFilledSizeLocation) {
        GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
            c.pViews_.value[i].BufferFilledSizeLocation);
        c.pViews_.bufferFilledSizeLocationKeys[i] = info.resourceKey;
        c.pViews_.bufferFilledSizeLocationOffsets[i] = info.offset;
      }
    }
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandList2WriteBufferImmediateCommand& c) {
  if (c.pParams_.value) {
    for (unsigned i = 0; i < c.Count_.value; ++i) {
      if (c.pParams_.value[i].Dest) {
        GpuAddressService::GpuAddressInfo info =
            manager_.getGpuAddressService().getGpuAddressInfo(c.pParams_.value[i].Dest);
        c.pParams_.destKeys[i] = info.resourceKey;
        c.pParams_.destOffsets[i] = info.offset;
      }
    }
  }
}

void CaptureCustomizationLayer::post(ID3D12FenceGetCompletedValueCommand& c) {
  static thread_local unsigned prevFenceKey = 0;
  static thread_local unsigned prevValue = 0;
  unsigned fenceKey = c.object_.key;
  unsigned value = c.result_.value;
  if (fenceKey == prevFenceKey && value == prevValue) {
    recorder_.skip(c.key);
  }
  prevFenceKey = fenceKey;
  prevValue = value;
}

void CaptureCustomizationLayer::pre(ID3D12FenceSetEventOnCompletionCommand& c) {
  manager_.getFenceService().setEventOnCompletion(c.object_.value, c.object_.key, c.Value_.value,
                                                  c.hEvent_.value);
}

void CaptureCustomizationLayer::pre(ID3D12Device1SetEventOnMultipleFenceCompletionCommand& c) {
  static bool printed = false;
  if (!printed) {
    Log(ERR) << "ID3D12Device1::SetEventOnMultipleFenceCompletion not handled!";
    printed = true;
  }
}

void CaptureCustomizationLayer::post(ID3D12DeviceOpenSharedHandleCommand& c) {
  if (c.result_.value != S_OK) {
    return;
  }
  if (c.riid_.value == IID_ID3D12Resource || c.riid_.value == IID_ID3D12Resource1 ||
      c.riid_.value == IID_ID3D12Resource2) {
    ID3D12Resource* resource = static_cast<ID3D12Resource*>(*c.ppvObj_.value);
    D3D12_RESOURCE_DESC desc = resource->GetDesc();
    D3D12_HEAP_PROPERTIES heapProperties{};
    D3D12_HEAP_FLAGS heapFlags{};
    HRESULT hr = resource->GetHeapProperties(&heapProperties, &heapFlags);
    GITS_ASSERT(hr == S_OK);

    ID3D12DeviceCreateCommittedResourceCommand createResource;
    createResource.key = manager_.createCommandKey();
    createResource.threadId = c.threadId;
    createResource.object_.key = c.object_.key;
    createResource.pHeapProperties_.value = &heapProperties;
    createResource.HeapFlags_.value = heapFlags;
    createResource.pDesc_.value = &desc;
    createResource.InitialResourceState_.value = D3D12_RESOURCE_STATE_COMMON;
    createResource.pOptimizedClearValue_.value = nullptr;
    createResource.riidResource_.value = c.riid_.value;
    createResource.ppvResource_.key = c.ppvObj_.key;
    recorder_.record(createResource.key,
                     new ID3D12DeviceCreateCommittedResourceWriter(createResource));

    manager_.updateCommandKey(c);

  } else if (c.riid_.value == IID_ID3D12Fence || c.riid_.value == IID_ID3D12Fence1) {
    ID3D12Fence* fence = static_cast<ID3D12Fence*>(*c.ppvObj_.value);
    UINT64 fenceValue = fence->GetCompletedValue();

    ID3D12DeviceCreateFenceCommand createFence;
    createFence.key = manager_.createCommandKey();
    createFence.threadId = c.threadId;
    createFence.object_.key = c.object_.key;
    createFence.InitialValue_.value = fenceValue;
    createFence.Flags_.value = D3D12_FENCE_FLAG_SHARED;
    createFence.riid_.value = c.riid_.value;
    createFence.ppFence_.key = c.ppvObj_.key;
    recorder_.record(createFence.key, new ID3D12DeviceCreateFenceWriter(createFence));

    manager_.updateCommandKey(c);
  } else {
    Log(ERR)
        << "ID3D12Device::OpenSharedHandle handled only for ID3D12Resource/1/2 and ID3D12Fence/1.";
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandList4BeginRenderPassCommand& c) {
  c.pRenderTargets_.descriptorKeys.resize(c.NumRenderTargets_.value);
  c.pRenderTargets_.descriptorIndexes.resize(c.NumRenderTargets_.value);
  for (unsigned i = 0; i < c.NumRenderTargets_.value; ++i) {
    if (c.pRenderTargets_.value && c.pRenderTargets_.value[i].cpuDescriptor.ptr) {
      CaptureDescriptorHandleService::HandleInfo info =
          manager_.getDescriptorHandleService().getDescriptorHandleInfo(
              D3D12_DESCRIPTOR_HEAP_TYPE_RTV, CaptureDescriptorHandleService::HandleType::CpuHandle,
              c.pRenderTargets_.value[i].cpuDescriptor.ptr);

      c.pRenderTargets_.descriptorKeys[i] = info.interfaceKey;
      c.pRenderTargets_.descriptorIndexes[i] = info.index;
    }
  }

  if (c.pDepthStencil_.value && c.pDepthStencil_.value->cpuDescriptor.ptr) {
    CaptureDescriptorHandleService::HandleInfo info =
        manager_.getDescriptorHandleService().getDescriptorHandleInfo(
            D3D12_DESCRIPTOR_HEAP_TYPE_DSV, CaptureDescriptorHandleService::HandleType::CpuHandle,
            c.pDepthStencil_.value->cpuDescriptor.ptr);

    c.pDepthStencil_.descriptorKey = info.interfaceKey;
    c.pDepthStencil_.descriptorIndex = info.index;
  }
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandList4BuildRaytracingAccelerationStructureCommand& c) {
  {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->DestAccelerationStructureData);
    c.pDesc_.destAccelerationStructureKey = info.resourceKey;
    c.pDesc_.destAccelerationStructureOffset = info.offset;
  }
  if (c.pDesc_.value->SourceAccelerationStructureData) {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->SourceAccelerationStructureData);
    c.pDesc_.sourceAccelerationStructureKey = info.resourceKey;
    c.pDesc_.sourceAccelerationStructureOffset = info.offset;
  }
  {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->ScratchAccelerationStructureData);
    c.pDesc_.scratchAccelerationStructureKey = info.resourceKey;
    c.pDesc_.scratchAccelerationStructureOffset = info.offset;
  }

  auto resolveInputsGpuAddress = [&](D3D12_GPU_VIRTUAL_ADDRESS address) {
    GpuAddressService::GpuAddressInfo info =
        manager_.getGpuAddressService().getGpuAddressInfo(address);
    c.pDesc_.inputKeys.push_back(info.resourceKey);
    c.pDesc_.inputOffsets.push_back(info.offset);
  };

  if (c.pDesc_.value->Inputs.Type == D3D12_RAYTRACING_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL) {
    resolveInputsGpuAddress(c.pDesc_.value->Inputs.InstanceDescs);
  } else {
    for (unsigned i = 0; i < c.pDesc_.value->Inputs.NumDescs; ++i) {
      const D3D12_RAYTRACING_GEOMETRY_DESC& desc =
          c.pDesc_.value->Inputs.DescsLayout == D3D12_ELEMENTS_LAYOUT_ARRAY
              ? c.pDesc_.value->Inputs.pGeometryDescs[i]
              : *c.pDesc_.value->Inputs.ppGeometryDescs[i];
      if (desc.Type == D3D12_RAYTRACING_GEOMETRY_TYPE_TRIANGLES) {
        resolveInputsGpuAddress(desc.Triangles.Transform3x4);
        resolveInputsGpuAddress(desc.Triangles.IndexBuffer);
        resolveInputsGpuAddress(desc.Triangles.VertexBuffer.StartAddress);
      } else if (desc.Type == D3D12_RAYTRACING_GEOMETRY_TYPE_PROCEDURAL_PRIMITIVE_AABBS) {
        resolveInputsGpuAddress(desc.AABBs.AABBs.StartAddress);
      }
    }
  }

  for (unsigned i = 0; i < c.NumPostbuildInfoDescs_.value; ++i) {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pPostbuildInfoDescs_.value[i].DestBuffer);
    c.pPostbuildInfoDescs_.destBufferKeys.push_back(info.resourceKey);
    c.pPostbuildInfoDescs_.destBufferOffsets.push_back(info.offset);
  }
}

void CaptureCustomizationLayer::pre(
    ID3D12GraphicsCommandList4CopyRaytracingAccelerationStructureCommand& c) {
  {
    GpuAddressService::GpuAddressInfo info =
        manager_.getGpuAddressService().getGpuAddressInfo(c.DestAccelerationStructureData_.value);
    c.DestAccelerationStructureData_.interfaceKey = info.resourceKey;
    c.DestAccelerationStructureData_.offset = info.offset;
  }
  {
    GpuAddressService::GpuAddressInfo info =
        manager_.getGpuAddressService().getGpuAddressInfo(c.SourceAccelerationStructureData_.value);
    c.SourceAccelerationStructureData_.interfaceKey = info.resourceKey;
    c.SourceAccelerationStructureData_.offset = info.offset;
  }
}

void CaptureCustomizationLayer::pre(ID3D12GraphicsCommandList4DispatchRaysCommand& c) {
  {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->RayGenerationShaderRecord.StartAddress);
    c.pDesc_.rayGenerationShaderRecordKey = info.resourceKey;
    c.pDesc_.rayGenerationShaderRecordOffset = info.offset;
  }
  {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->MissShaderTable.StartAddress);
    c.pDesc_.missShaderTableKey = info.resourceKey;
    c.pDesc_.missShaderTableOffset = info.offset;
  }
  {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->HitGroupTable.StartAddress);
    c.pDesc_.hitGroupTableKey = info.resourceKey;
    c.pDesc_.hitGroupTableOffset = info.offset;
  }
  {
    GpuAddressService::GpuAddressInfo info = manager_.getGpuAddressService().getGpuAddressInfo(
        c.pDesc_.value->CallableShaderTable.StartAddress);
    c.pDesc_.callableShaderTableKey = info.resourceKey;
    c.pDesc_.callableShaderTableOffset = info.offset;
  }
}

void CaptureCustomizationLayer::pre(INTC_D3D12_CreateDeviceExtensionContextCommand& c) {
  if (c.pExtensionAppInfo_.value) {
    c.pExtensionAppInfo_.pApplicationName = c.pExtensionAppInfo_.value->pApplicationName;
    c.pExtensionAppInfo_.pEngineName = c.pExtensionAppInfo_.value->pEngineName;
  }
}

void CaptureCustomizationLayer::pre(INTC_D3D12_CreateDeviceExtensionContext1Command& c) {
  if (c.pExtensionAppInfo_.value) {
    c.pExtensionAppInfo_.pApplicationName = c.pExtensionAppInfo_.value->pApplicationName;
    c.pExtensionAppInfo_.pEngineName = c.pExtensionAppInfo_.value->pEngineName;
  }
}

void CaptureCustomizationLayer::pre(INTC_D3D12_CreateComputePipelineStateCommand& c) {
  c.pDesc_.cs = c.pDesc_.value->CS.pShaderBytecode;
  c.pDesc_.compileOptions = c.pDesc_.value->CompileOptions;
  c.pDesc_.internalOptions = c.pDesc_.value->InternalOptions;
}

void CaptureCustomizationLayer::pre(IDMLDeviceCreateBindingTableCommand& c) {
  DescriptorHandleArgument<D3D12_CPU_DESCRIPTOR_HANDLE> cpuDescHandle = {
      c.desc_.value->CPUDescriptorHandle};
  fillCpuDescriptorHandleArgument(cpuDescHandle, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  c.desc_.data.cpuDescHandleKey = cpuDescHandle.interfaceKey;
  c.desc_.data.cpuDescHandleIndex = cpuDescHandle.index;

  DescriptorHandleArgument<D3D12_GPU_DESCRIPTOR_HANDLE> gpuDescHandle = {
      c.desc_.value->GPUDescriptorHandle};
  fillGpuDescriptorHandleArgument(gpuDescHandle, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  c.desc_.data.gpuDescHandleKey = gpuDescHandle.interfaceKey;
  c.desc_.data.gpuDescHandleIndex = gpuDescHandle.index;
}

void CaptureCustomizationLayer::pre(IDMLBindingTableResetCommand& c) {
  DescriptorHandleArgument<D3D12_CPU_DESCRIPTOR_HANDLE> cpuDescHandle = {
      c.desc_.value->CPUDescriptorHandle};
  fillCpuDescriptorHandleArgument(cpuDescHandle, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  c.desc_.data.cpuDescHandleKey = cpuDescHandle.interfaceKey;
  c.desc_.data.cpuDescHandleIndex = cpuDescHandle.index;

  DescriptorHandleArgument<D3D12_GPU_DESCRIPTOR_HANDLE> gpuDescHandle = {
      c.desc_.value->GPUDescriptorHandle};
  fillGpuDescriptorHandleArgument(gpuDescHandle, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
  c.desc_.data.gpuDescHandleKey = gpuDescHandle.interfaceKey;
  c.desc_.data.gpuDescHandleIndex = gpuDescHandle.index;
}

void CaptureCustomizationLayer::fillGpuAddressArgument(D3D12_GPU_VIRTUAL_ADDRESS_Argument& arg) {
  if (arg.value) {
    GpuAddressService::GpuAddressInfo info =
        manager_.getGpuAddressService().getGpuAddressInfo(arg.value);
    arg.interfaceKey = info.resourceKey;
    arg.offset = info.offset;
  }
}

void CaptureCustomizationLayer::fillGpuDescriptorHandleArgument(
    DescriptorHandleArgument<D3D12_GPU_DESCRIPTOR_HANDLE>& arg,
    D3D12_DESCRIPTOR_HEAP_TYPE heapType) {

  CaptureDescriptorHandleService::HandleInfo info =
      manager_.getDescriptorHandleService().getDescriptorHandleInfo(
          heapType, CaptureDescriptorHandleService::HandleType::GpuHandle, arg.value.ptr);

  arg.interfaceKey = info.interfaceKey;
  arg.index = info.index;
}

void CaptureCustomizationLayer::fillCpuDescriptorHandleArgument(
    DescriptorHandleArgument<D3D12_CPU_DESCRIPTOR_HANDLE>& arg,
    D3D12_DESCRIPTOR_HEAP_TYPE heapType) {

  CaptureDescriptorHandleService::HandleInfo info =
      manager_.getDescriptorHandleService().getDescriptorHandleInfo(
          heapType, CaptureDescriptorHandleService::HandleType::CpuHandle, arg.value.ptr);

  arg.interfaceKey = info.interfaceKey;
  arg.index = info.index;
}

} // namespace DirectX
} // namespace gits
