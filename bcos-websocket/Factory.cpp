/*
 *  Copyright (C) 2021 FISCO BCOS.
 *  SPDX-License-Identifier: Apache-2.0
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 * @file Factory.cpp
 * @author: octopus
 * @date 2021-08-21
 */

#include <bcos-websocket/Factory.h>
#include <bcos-websocket/WsConnector.h>
#include <bcos-websocket/WsMessage.h>
#include <memory>

using namespace bcos;
using namespace bcos::ws;

bcos::ws::WsService::Ptr Factory::buildWsService()
{
    auto ioc = std::make_shared<boost::asio::io_context>();
    auto resolver = std::make_shared<boost::asio::ip::tcp::resolver>(*ioc);
    auto connector = std::make_shared<WsConnector>(resolver, ioc);
    auto messageFactory = std::make_shared<bcos::ws::WsMessageFactory>();
    auto wsService = std::make_shared<bcos::ws::WsService>();
    auto threadPool = std::make_shared<bcos::ThreadPool>("t_cppsdk", m_config->threadPoolSize());

    wsService->setConfig(m_config);
    wsService->setThreadPool(threadPool);
    wsService->setIoc(ioc);
    wsService->setConnector(connector);
    wsService->setMessageFactory(messageFactory);
    wsService->initMethod();
    return wsService;
}