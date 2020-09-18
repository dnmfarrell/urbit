import React, { ReactNode, useState } from "react";
import {
  Box,
  Row,
  Text,
  Icon,
  MenuItem as _MenuItem,
  IconButton,
} from "@tlon/indigo-react";
import { capitalize } from "lodash";

import { SidebarInvite } from "./SidebarInvite";
import GlobalApi from "~/logic/api/global";
import { AppName } from "~/types/noun";
import { alphabeticalOrder } from "~/logic/lib/util";
import { GroupSwitcher } from "~/views/apps/groups/components/GroupSwitcher";
import { AppInvites, Associations, AppAssociations } from "~/types";
import { SidebarItem } from "./SidebarItem";
import {
  SidebarListHeader,
  SidebarListConfig,
  SidebarSort,
} from "./SidebarListHeader";
import { useLocalStorageState } from "~/logic/lib/useLocalStorageState";

interface SidebarAppConfig {
  name: string;
  makeRouteForResource: (appPath: string) => string;
  getStatus: (appPath: string) => SidebarItemStatus | undefined;
}

export type SidebarAppConfigs = { [a in AppName]: SidebarAppConfig };

export type SidebarItemStatus =
  | "unread"
  | "mention"
  | "unsubscribed"
  | "disconnected"
  | "loading";

function sidebarSort(
  associations: AppAssociations
): Record<SidebarSort, (a: string, b: string) => number> {
  const alphabetical = (a: string, b: string) => {
    const aAssoc = associations[a];
    const bAssoc = associations[b];
    const aTitle = aAssoc?.metadata?.title || b;
    const bTitle = bAssoc?.metadata?.title || b;

    return alphabeticalOrder(aTitle, bTitle);
  };

  return {
    asc: alphabetical,
    desc: (a, b) => alphabetical(b, a),
  };
}

const apps = ["chat", "publish", "link"];

function SidebarItems(props: {
  apps: SidebarAppConfigs;
  config: SidebarListConfig;
  associations: Associations;
  group: string;
  selected?: string;
}) {
  const { selected, group, config } = props;
  const associations = {
    ...props.associations.chat,
    ...props.associations.publish,
    ...props.associations.link,
  };

  const ordered = Object.keys(associations)
    .filter((a) => {
      const assoc = associations[a];
      return assoc["group-path"] === group;
    })
    .sort(sidebarSort(associations)[config.sortBy]);

  return (
    <>
      {ordered.map((path) => {
        const assoc = associations[path];
        return (
          <SidebarItem
            key={path}
            path={path}
            selected={path === selected}
            association={assoc}
            apps={props.apps}
            hideUnjoined={config.hideUnjoined}
          />
        );
      })}
    </>
  );
}

interface SidebarProps {
  children: ReactNode;
  recentGroups: string[];
  invites: AppInvites;
  api: GlobalApi;
  associations: Associations;
  selected?: string;
  selectedGroup: string;
  apps: SidebarAppConfigs;
  baseUrl: string;
  mobileHide?: boolean;
}

export function Sidebar(props: SidebarProps) {
  const { invites, api, associations, selected, apps } = props;
  const groupAsssociation = associations.contacts[props.selectedGroup];
  const display = props.mobileHide ? ["none", "flex"] : "flex";
  if (!groupAsssociation) {
    return null;
  }
  if (!associations) {
    return null;
  }

  const [config, setConfig] = useLocalStorageState<SidebarListConfig>(
    `group-config:${props.selectedGroup}`,
    {
      sortBy: "asc",
      hideUnjoined: false,
    }
  );
  return (
    <Box
      display={display}
      flexDirection="column"
      width="100%"
      gridRow="1/3"
      gridColumn="1/2"
      borderRight={1}
      borderRightColor="washedGray"
      overflowY="auto"
      fontSize={0}
      bg="white"
      position="relative"
    >
      <GroupSwitcher
        associations={associations}
        recentGroups={props.recentGroups}
        baseUrl={props.baseUrl}
        association={groupAsssociation}
      />
      {Object.keys(invites).map((appPath) =>
        Object.keys(invites[appPath]).map((uid) => (
          <SidebarInvite
            key={uid}
            invite={props.invites[uid]}
            onAccept={() => props.api.invite.accept(appPath, uid)}
            onDecline={() => props.api.invite.decline(appPath, uid)}
          />
        ))
      )}
      <SidebarListHeader initialValues={config} handleSubmit={setConfig} />
      <SidebarItems
        config={config}
        associations={associations}
        selected={selected}
        group={props.selectedGroup}
        apps={props.apps}
      />
    </Box>
  );
}
