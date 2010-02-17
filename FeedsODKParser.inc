<?php

class FeedsODKParser extends FeedsParser {
  /**
   * Implement FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    if (!class_exists('FeedsODKBatch') || !($batch instanceof FeedsODKBatch)) {
      throw Exception(t('ODK Parser needs to be paired with ODK Fetcher'));
    }
    $parsed = $this->parseXML($batch->getRaw());
    feeds_odk_log($parsed);
    $batch->setItems(array($parsed));
  }

  /**
   * Parse the submitted XML.
   */
  protected function parseXML($raw) {
    $xml = @ new SimpleXMLElement($raw);
    list($lat, $lon, $alt, $acc) = explode(' ', (string) @current($xml->xpath('/geotagger/Location')));
    return array(
      'device_id' => (string) @current($xml->xpath('/geotagger/DeviceId')),
      'image' => (string) @current($xml->xpath('/geotagger/Image')),
      'latitude' => $lat,
      'longitude' => $lon,
      'altitude' => $alt,
      'accuracy' => $acc,
      'description' => (string) @current($xml->xpath('/geotagger/Description')),
      );
  }
}