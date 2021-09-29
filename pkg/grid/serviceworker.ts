/* eslint-disable no-restricted-globals */
import { fetchEventSource } from '@microsoft/fetch-event-source';
import { registerRoute } from 'workbox-routing';

self.addEventListener('install', () => {
  self.skipWaiting();
});

self.addEventListener('activate', (ev) => {
  ev.waitUntil(self.clients.claim());
});

/**
 * EventStream Proxy
 */

// Headers for SSE response
const sseHeaders = {
  'content-type': 'text/event-stream',
  'Transfer-Encoding': 'chunked',
  Connection: 'keep-alive'
};
const encoder = new TextEncoder();
// Map with server connections, where key - url, value - EventSource
const serverConnection = {};
// For each request opens only one server connection and use it for next requests with the same url
async function getServerConnection(url) {
  if (!serverConnection.url) {
    serverConnection.url = url;
  }

  if (!serverConnection.source) {
    const listeners = [];
    const source = new AbortController();
    fetchEventSource(serverConnection.url || url, {
      credentials: 'include',
      accept: '*',
      headers: {
        'Content-Type': 'application/json'
      },
      signal: source.signal,
      openWhenHidden: true,
      onmessage: (event) => {
        const parsedData = JSON.parse(event.data);
        serverConnection.eventId = parseInt(parsedData.id, 10);

        const responseData = encodeEvent(event);
        const handlers = serverConnection.listeners.slice();
        handlers.forEach(({ handle }) => {
          handle(responseData);
        });
      }
    });

    serverConnection.source = source;
    serverConnection.listeners = listeners;
    serverConnection.count = 0;
    serverConnection.eventId = 0;
  }

  return serverConnection;
}

registerRoute(
  ({ request }) => {
    const { headers } = request;
    return headers.get('Accept') === 'text/event-stream';
  },
  async ({ url }) => {
    const id = url.searchParams.get('id');
    url.searchParams.delete('id');
    const connection = await getServerConnection(url.href);

    const stream = new ReadableStream({
      start: (controller) => {
        controller.enqueue(encodeEvent({ data: 'hello!' }));
        connection.count += 1;
        console.log('current', connection.count, id);

        connection.listeners.push({
          id,
          handle: (responseData) => controller.enqueue(responseData),
          close: () => controller.close()
        });
      }
    });

    console.log('initiating stream', serverConnection.url);
    return new Response(stream, { headers: sseHeaders });
  }
);

const handlerMap = {
  GET_CHANNEL: getChannel,
  CLOSE_STREAM: closeStream
};

self.addEventListener('message', async (event) => {
  if (!event.data) {
    return;
  }

  const handler = handlerMap[event.data.type];

  if (handler) {
    await handler(event.data);
  }
});

function getChannel() {
  self.clients
    .matchAll({
      includeUncontrolled: true,
      type: 'window'
    })
    .then((clients) => {
      const message = {
        type: 'CURRENT_CHANNEL',
        eventId: serverConnection.eventId,
        channel: serverConnection.url
      };

      console.log(message);
      if (clients && clients.length) {
        clients.forEach((client) => client.postMessage(message));
      }
    });
}

async function closeStream({ url, id }) {
  const connection = await getServerConnection(url);

  if (connection.count <= 1) {
    clearConnection();
  } else {
    const index = connection.listeners.findIndex((item) => item.id === id);
    let listener = connection.listeners[index];
    if (!listener) {
      return;
    }

    connection.listeners.splice(index, 1);
    connection.count -= 1;
    listener.close();
    listener = null;

    console.log({ url, count: connection.count, listeners: connection.listeners });
  }
}

function clearConnection(url) {
  serverConnection.source.abort();

  delete serverConnection.url;
  delete serverConnection.source;
  delete serverConnection.listeners;
  delete serverConnection.count;

  fetch(url, {
    body: JSON.stringify([{ action: 'delete' }]),
    method: 'PUT'
  });
  console.log('closing', url);
}

function encodeEvent({ data, event, retry, id }) {
  const responseText = sseChunkData(data, event, retry, id);
  return encoder.encode(responseText);
}

// Function for formatting message to SSE response
function sseChunkData(data, event, retry, id) {
  return `${Object.entries({ event, id, data, retry })
    .filter(([, value]) => ![undefined, null].includes(value))
    .map(([key, value]) => `${key}: ${value}`)
    .join('\n')}\n\n`;
}
