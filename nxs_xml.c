#include <libxml/xmlreader.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "nxs.h"
#include "nxs_xml.h"

void _NXS_XMLParseData(xmlDocPtr, xmlNodePtr, void (*XMLEntryCallback)(NexusArtifact_t*));
NXS_XMLParseSearch(char *xml, void (*XMLEntryCallback)(NexusArtifact_t*)){
    //printf("xml parsed: %s\n", xml);
    xmlDocPtr  xml_doc = xmlParseDoc(xml);
    xmlNodePtr xml_cur_node = xmlDocGetRootElement(xml_doc);
    xml_cur_node = xmlDocGetRootElement(xml_doc);
    xml_cur_node = xml_cur_node->xmlChildrenNode;
    while (xml_cur_node != NULL) {
        // Get search-results
        if ((!xmlStrcmp(xml_cur_node->name, (const xmlChar *)"data"))){
          _NXS_XMLParseData(xml_doc, xml_cur_node, XMLEntryCallback);
          //printf("%s\n", xmlNodeListGetString(xml_doc, xml_cur_node->xmlChildrenNode, 1));
        }
        xml_cur_node = xml_cur_node->next;
    }
    xmlFreeDoc(xml_doc);
}
void _NXS_XMLParseData(xmlDocPtr xml_doc, xmlNodePtr xml_ptr, void (*XMLEntryCallback)(NexusArtifact_t*)) {
  NexusArtifact_t artifact;
  xmlNodePtr data_ptr, artifact_ptr;
  xml_ptr = xml_ptr->xmlChildrenNode;
  data_ptr = xml_ptr;
  //printf("%s\n", xml_ptr->name);
  while (data_ptr != NULL) {
    if ((!xmlStrcmp(data_ptr->name, (const xmlChar *)"artifact"))) {
      //printf("%s ", data_ptr->name);
      artifact_ptr = data_ptr->xmlChildrenNode;
      while (artifact_ptr != NULL) {
        if ((!xmlStrcmp(artifact_ptr->name, (const xmlChar *)"groupId"))) {
          strcpy_s(artifact.groupId, STRING_SIZE, xmlNodeListGetString(xml_doc, artifact_ptr->xmlChildrenNode, 1));
        }
        if ((!xmlStrcmp(artifact_ptr->name, (const xmlChar *)"artifactId"))) {
          strcpy_s(artifact.artifactId, STRING_SIZE, xmlNodeListGetString(xml_doc, artifact_ptr->xmlChildrenNode, 1));
        }
        if ((!xmlStrcmp(artifact_ptr->name, (const xmlChar *)"version"))) {
          strcpy_s(artifact.version, STRING_SIZE, xmlNodeListGetString(xml_doc, artifact_ptr->xmlChildrenNode, 1));
        }
        if ((!xmlStrcmp(artifact_ptr->name, (const xmlChar *)"classifier"))) {
          strcpy_s(artifact.classifier, STRING_SIZE, xmlNodeListGetString(xml_doc, artifact_ptr->xmlChildrenNode, 1));
        }
        artifact_ptr = artifact_ptr->next;
      }
      XMLEntryCallback(&artifact);
      ZeroMemory(artifact.groupId, STRING_SIZE);
      ZeroMemory(artifact.artifactId, STRING_SIZE);
      ZeroMemory(artifact.classifier, STRING_SIZE);
      ZeroMemory(artifact.version, STRING_SIZE);
      ZeroMemory(artifact.resourceURI, STRING_SIZE);

    }
    data_ptr = data_ptr->next;
  }
  //printf("%s\n", xmlNodeListGetString(xml_doc, xml_ptr->xmlChildrenNode, 1));
}
